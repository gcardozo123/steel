#include <iostream>

#include "flecs.h"

#include "game.hpp"
#include "game_info.hpp"
#include "components.hpp"
#include "log.hpp"

namespace Steel
{

Game::Game()
    :
    world(nullptr),
    is_running(false),
    game_info(CreateSharedPtr<GameInfo>()),
    window(nullptr),
    renderer(nullptr),
    assets(nullptr)
{}
Game::~Game()
{}
	
void Game::Init(std::string window_title, int window_width, int window_height, bool is_window_resizable, float desired_fps)
{   
    this->game_info->SetDesiredFps(desired_fps);
    this->game_info->SetWindowWidth(window_width);
    this->game_info->SetWindowHeight(window_height);
    this->game_info->SetWindowResizable(is_window_resizable);
    this->game_info->SetWindowTitle(window_title);
    this->game_info->SetTimeScale(1.0);

    this->world = CreateSharedPtr<flecs::world>();
    this->world->set_target_fps(this->game_info->GetDesiredFps());

    this->InitializeRenderer();
    this->RegisterComponents();
    
    assets.SetRenderer(this->renderer);
}

void Game::InitializeRenderer()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        STEEL_CORE_ASSERT(false, "Error initializing SDL.");
        SDL_Quit();
        return;
    }
    if (TTF_Init() != 0)
    {
        STEEL_CORE_ASSERT(false, "Error initializing SDL TTF");
        SDL_Quit();
        return;
    }
    Uint32 sdl_flags = (
        game_info->IsWindowResizable() ?
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE : SDL_WINDOW_SHOWN
        );
    window = SdlSharedPtr(
        SDL_CreateWindow(
            game_info->GetWindowTitle().c_str(),
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            game_info->GetWindowWidth(),
            game_info->GetWindowHeight(),
            sdl_flags
        )
    );
    if (!window)
    {
        STEEL_CORE_ASSERT(false, "Error creating SDL window.");
        SDL_Quit();
        return;
    }
    renderer = SdlSharedPtr(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    );
    if (!renderer)
    {
        STEEL_CORE_ASSERT(false, "Error creating SDL renderer.");
        SDL_Quit();
        return;
    }
}

void Game::RegisterComponents()
{
    flecs::component<TransformComponent>(*this->world);
    flecs::component<TextureComponent>(*this->world);
}


void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
        {
            this->Quit();
            break;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                this->Quit();
            }
        }
        default:
        {
            break;
        }
    }
}

void Game::Run()
{
    auto sdl_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    STEEL_CORE_ASSERT(
        sdl_init & SDL_INIT_EVERYTHING,
        "SDL wasn't initialized. Missing call to `InitializeRenderer`."
    );

    this->is_running = true;
    while (this->is_running) 
    {
        ProcessInput();
        //TODO: process Windows events
        this->world->progress();
        this->Render();
    }
}

void Game::Render()
{
    //set background color:
    SDL_SetRenderDrawColor(renderer.get(), 50, 50, 80, 255);
    //clear back buffer:
    SDL_RenderClear(renderer.get());

    // TODO: 
    // 1. query all entities that have Transform + Texture
    // 2. render each one accordingly
    // How? Add a `Assets` class, responsible for loading all types of
    // resources (images, audios, fonts, etc). Game or Resource will be 
    // responsible for binding the resource ID (a name? or SdlTexture directly?) to a given component.
    // Create a query for all entities with Position, Velocity
    
    auto query = this->world->query<TextureComponent, TransformComponent>();
    query.each([&](
        flecs::entity e, 
        TextureComponent& texture_component, 
        const TransformComponent& transform_component
    ){
        //std::cout << "Entity name: " << e.name() << std::endl;
        
        auto sdl_texture = texture_component.texture;
        if (sdl_texture != nullptr)
        {
            int w, h;
            SDL_QueryTexture(sdl_texture.get(), nullptr, nullptr, &w, &h);
            SDL_FRect dest;
            dest.w = transform_component.scale.x * (float) w;
            dest.h = transform_component.scale.y * (float) h;
            dest.x = transform_component.position.x;
            dest.y = transform_component.position.y;
            //TODO decide between SDL_RenderCopy and SDL_RenderCopyF (consider pixel perfect movement)
            SDL_RenderCopyExF(
            this->renderer.get(),
            sdl_texture.get(),
            nullptr,
            &dest,
            transform_component.rotation,
            nullptr,
            SDL_RendererFlip::SDL_FLIP_NONE
            );
        }

    });

    //swap front and back buffers:
    SDL_RenderPresent(this->renderer.get());
}

void Game::Quit()
{
    this->is_running = false;
}

SharedPtr<flecs::world> Game::GetWorld()
{
    return this->world;
}

}