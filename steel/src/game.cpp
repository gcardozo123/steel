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
    scene_root(nullptr),
    is_running(false),
    game_info(CreateSharedPtr<GameInfo>()),
    window(nullptr),
    renderer(nullptr),
    assets(nullptr)
{}
Game::~Game()
{}
	
void Game::Init(
    std::string window_title,
    int window_width,
    int window_height,
    Steel::Color background_color,
    bool is_window_resizable,
    float desired_fps
){
    this->game_info->SetBackgroundColor(background_color);
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
    this->scene_root = CreateSharedPtr<flecs::entity>(
            world->entity("SceneRoot").set<TransformComponent>(TransformComponent())
    );
    
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
    this->world->component<TransformComponent>();
    this->world->component<TextureComponent>();
    this->world->component<VelocityComponent>();
    this->world->component<LineComponent>();
    this->world->component<RectangleComponent>();
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
    const Color& bg_color = game_info->GetBackgroundColor();
    SDL_SetRenderDrawColor(renderer.get(), bg_color.R(), bg_color.G(), bg_color.B(), bg_color.A());
    SDL_RenderClear(renderer.get()); //clear back buffer

    //TODO: think how can I define different layers
    //TODO: handle hierarchical entities (position += parent.position):
    //  https://github.com/SanderMertens/flecs/blob/master/examples/cpp/08_hierarchy/src/main.cpp
    this->world->query<TextureComponent, TransformComponent>().each(
        std::bind(&Game::RenderTexture, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );
    this->world->query<RectangleComponent, TransformComponent>().each(
        std::bind(&Game::RenderRectangle, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );
    this->world->query<LineComponent, TransformComponent>().each(
        std::bind(&Game::RenderLine, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );

    //swap front and back buffers:
    SDL_RenderPresent(this->renderer.get());
}

void Game::UpdateTransforms(flecs::entity e, TransformComponent &transform_component)
{

}

void Game::RenderTexture(
    flecs::entity e, TextureComponent &texture_component, const TransformComponent &transform_component)
{
    auto sdl_texture = texture_component.texture;
    if (!sdl_texture || (!texture_component.is_visible))
    {
        return;
    }
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

void Game::RenderRectangle(flecs::entity e, RectangleComponent& rect_component, const TransformComponent &transform_component)
{
    if (!rect_component.is_visible)
    {
        return;
    }
    SDL_SetRenderDrawColor(
        this->renderer.get(),
        rect_component.color.R(),
        rect_component.color.G(),
        rect_component.color.B(),
        rect_component.color.A()
    );
//TODO check how to handle hierarchies with flecs:
// https://github.com/SanderMertens/flecs/blob/master/examples/cpp/08_hierarchy/src/main.cpp
//    const Math::Vector2& position = e.has<TransformComponent>() ? e.get<TransformComponent>()->position : Math::Vector2();
//    float x = rect_component.x + position.x;
//    float y = rect_component.y + position.y;
    SDL_FRect rect{rect_component.x, rect_component.y, rect_component.width, rect_component.height};
    if (rect_component.is_filled)
    {
        //TODO: SDL_RenderFillRectsF apparently supports batching, so that is something to consider here
        SDL_RenderFillRectF(this->renderer.get(), &rect);
    }
    else
    {
        //SDL_RenderDrawRectsF just does N calls to SDL_RenderDrawRectF, so no need to worry into changing to
        // SDL_RenderDrawRectsF here
        SDL_RenderDrawRectF(this->renderer.get(), &rect);
    }
}

void Game::RenderLine(flecs::entity e, LineComponent& line_component, const TransformComponent &transform_component)
{
    if (!line_component.is_visible)
    {
        return;
    }
    SDL_SetRenderDrawColor(
        this->renderer.get(),
        line_component.color.R(),
        line_component.color.G(),
        line_component.color.B(),
        line_component.color.A()
    );
    //TODO: SDL_RenderDrawLinesF apparently supports batching, so that's something to consider here
    SDL_RenderDrawLineF(
        this->renderer.get(), line_component.p1.x, line_component.p1.y, line_component.p2.x, line_component.p2.y
    );
}

void Game::Quit()
{
    this->is_running = false;
}

SharedPtr<flecs::world> Game::GetWorld()
{
    return this->world;
}

SharedPtr<flecs::entity> Game::GetSceneRoot()
{
    return this->scene_root;
}

}