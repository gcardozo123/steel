#include <iostream>

#include "flecs.h"

#include "components.hpp"
#include "game.hpp"
#include "game_info.hpp"
#include "log.hpp"
#include "steel_sdl.hpp"


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
	
void Game::Init(std::string window_title, int window_width, int window_height, bool is_window_resizable)
{   
    this->game_info->SetDesiredFps(60.0f);
    this->game_info->SetWindowWidth(window_width);
    this->game_info->SetWindowHeight(window_height);
    this->game_info->SetWindowResizable(is_window_resizable);
    this->game_info->SetWindowTitle(window_title);
    this->game_info->SetTimeScale(1.0);

    this->world = CreateSharedPtr<flecs::world>();
    this->world->set_target_fps(this->game_info->GetDesiredFps());

    this->_InitializeRenderer();
    this->_RegisterComponents();
    
    assets.SetRenderer(this->renderer);
}

void Game::_InitializeRenderer()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        SDL_Quit();
        return;
    }
    if (TTF_Init() != 0)
    {
        std::cerr << "Error initializing SDL TTF" << std::endl;
        SDL_Quit();
        return;
    }
    Uint32 sdlFlags = (
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
            sdlFlags
        )
    );
    if (!window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        SDL_Quit();
        return;
    }
    renderer = SdlSharedPtr(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    );
    if (!renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        SDL_Quit();
        return;
    }
}

void Game::_RegisterComponents()
{
    flecs::component<TransformComponent>(*this->world);
    flecs::component<TextureComponent>(*this->world);
}


void Game::_ProcessInput()
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
        "SDL wasn't initialized. Missing call to `_InitializeRenderer`."
    );

    this->is_running = true;
    while (this->is_running) 
    {
        _ProcessInput();
        //TODO: process system events
        //TODO: update actors
        this->_Render();
        this->world->progress();
    }
}

void Game::_Render()
{
    //set background color:
    SDL_SetRenderDrawColor(renderer.get(), 50, 50, 80, 255);
    //clear back buffer:
    SDL_RenderClear(renderer.get());

    // TODO: 
    // 1. query all entites that have Transform + Texture
    // 2. render each one accordingly
    // How? Add a `Resource` class, responsible for loading all types of 
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
            SDL_QueryTexture(sdl_texture.get(), NULL, NULL, &w, &h);
            //TODO handle rotation
            SDL_Rect dest;
            dest.w = w * transform_component.scale.x;
            dest.h = h * transform_component.scale.y;
            dest.x = transform_component.position.x;
            dest.y = transform_component.position.y;
            SDL_RenderCopy(this->renderer.get(), sdl_texture.get(), 0, &dest);
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