#include "game.hpp"
#include "game_info.hpp"
#include "components.hpp"
#include "component_utils.hpp"
#include "asserts.hpp"
#include "steel_math.hpp"

namespace Steel
{

Game::Game(const GameInfo* game_info)
    :
    scene_root(entt::null),
    is_running(false),
    game_info(game_info),
    window(nullptr),
    renderer(nullptr),
    update_game_func( []( Steel::DeltaTime ) {} )
{}

Game::~Game() = default;
	
void Game::Init(){
    Log::Init();
    InitializeRenderer();
    InitializeEntities();
    assets.SetRenderer(renderer.get());
}

void Game::InitializeRenderer()
{
    STEEL_CORE_ASSERT(
        game_info->rendering_mode == RenderingMode::PixelPerfect, "Only 'PixelPerfect' rendering is supported for now"
    );
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
        game_info->is_window_resizable ?
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE : SDL_WINDOW_SHOWN
    );
    window = SdlMakeUniquePtr(
            SDL_CreateWindow(
                    game_info->window_title.c_str(),
                    SDL_WINDOWPOS_CENTERED,
                    SDL_WINDOWPOS_CENTERED,
                    game_info->window_width,
                    game_info->window_height,
                    sdl_flags
            )
    );
    if (!window)
    {
        STEEL_CORE_ASSERT(false, "Error creating SDL window.");
        SDL_Quit();
        return;
    }
    renderer = SdlMakeSharedPtr( SDL_CreateRenderer(
        window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    ));
    if (!renderer)
    {
        STEEL_CORE_ASSERT(false, "Error creating SDL renderer.");
        SDL_Quit();
        return;
    }
    SDL_SetRenderDrawBlendMode(renderer.get(), SDL_BLENDMODE_BLEND);
    SDL_RenderSetLogicalSize(renderer.get(), game_info->window_width, game_info->window_height ); // keep game aspect ratio
}

void Game::ProcessInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
        case SDL_QUIT:
        {
            Quit();
            break;
        }
        case SDL_KEYDOWN:
        {
            if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                Quit();
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
    //Reference:
    // commit 28a97f148cb8ffaef3e998a9c8d05a237431af86 has Glaiel's system
    // https://medium.com/@tglaiel/how-to-make-your-game-run-at-60fps-24c61210fe75
    // https://github.com/TylerGlaiel/FrameTimingControl/blob/master/frame_timer.cpp

    auto sdl_init = SDL_WasInit(SDL_INIT_EVERYTHING);
    STEEL_CORE_ASSERT(
        sdl_init & SDL_INIT_EVERYTHING,
        "SDL wasn't initialized. Missing call to `InitializeRenderer`."
    );

    double update_rate = game_info->desired_fps;
    double update_multiplicity = game_info->update_multiplicity;

    // compute how many ticks one update should be
    DeltaTime fixed_delta_time = 1.0 / update_rate;
    int64_t desired_frame_time = SDL_GetPerformanceFrequency() / update_rate;

    // these are to snap deltaTime to vsync values if it's close enough
    int64_t vsync_max_error = SDL_GetPerformanceFrequency() * .0002;
    // since this is about snapping to common vsync values
    int64_t time_60hz = SDL_GetPerformanceFrequency() / 60;

    int64_t snap_frequencies[] = {
            time_60hz,          //60fps
            time_60hz * 2,      //30fps
            time_60hz * 3,      //20fps
            time_60hz * 4,      //15fps
            //120fps //120hz, 240hz, or higher need to round up, so that adding 120hz twice guaranteed
            // is at least the same as adding time_60hz once
            (time_60hz + 1) / 2,
            // (time_60hz+2)/3,  //180fps //that's where the +1 and +2 come from in those equations
            //240fps //I do not want to snap to anything higher than 120 in my engine, but I left the math in here anyway
            // (time_60hz+3)/4,
    };

    //This is for delta time averaging
    //I know you can and should use a ring buffer for this, but I didn't want to include dependencies in this sample code
    const int time_history_count = 4;
    int64_t time_averager[time_history_count] = {
        desired_frame_time, desired_frame_time, desired_frame_time, desired_frame_time
    };

    //These are stored in my Application class and are not local variables in production code
    bool resync = true;
    int64_t prev_frame_time = SDL_GetPerformanceCounter();
    int64_t frame_accumulator = 0;

    // Update logic once before the game loop so transforms are properly initialized
    // TODO: remove this after "frame_accumulator starting as zero and skipping UpdateLogic" is fixed
    UpdateLogic(fixed_delta_time);

    is_running = true;
    while (is_running)
    {
        //frame timer
        int64_t current_frame_time = SDL_GetPerformanceCounter();
        int64_t delta_time = current_frame_time - prev_frame_time;
        prev_frame_time = current_frame_time;
        //STEEL_INFO("update: {0}", (1.0 / desired_frame_time * 1000 * 10000));

        //handle unexpected timer anomalies (overflow, extra slow frames, etc)
        //ignore extra-slow frames (this is 8/60 (7.5fps))
        if (delta_time > desired_frame_time * 8)
        {
            delta_time = desired_frame_time;
        }
        // If delta time is less than 0, that means that the system timer wrapped around (overflow)
        if (delta_time < 0)
        {
            delta_time = 0;
        }

        //vsync time snapping
        for (int64_t snap : snap_frequencies)
        {
            if (std::abs(delta_time - snap) < vsync_max_error)
            {
                delta_time = snap;
                break;
            }
        }

        //delta time averaging
        for (int i = 0; i < time_history_count - 1; i++)
        {
            time_averager[i] = time_averager[i + 1];
        }
        time_averager[time_history_count - 1] = delta_time;
        delta_time = 0;
        for (int i = 0; i < time_history_count; i++)
        {
            delta_time += time_averager[i];
        }
        delta_time /= time_history_count;
        // TODO: framerate is spiking when game starts then stays around 60fps (independent of desired_fps)
        //printf("fps: %f\n", (1.0 / delta_time * 1000 * 10000));

        //add to the accumulator
        frame_accumulator += delta_time;

        //spiral of death protection
        //If your game cannot *update* at 60hz, you end up in a spiral of doom where your
        //game can never catch up to where it should be, and so it will do more and more
        //updates every time until it eventually just freezes. Let's cap the accumulator to
        //a maximum (8/60 (7.5fps)) and it should prevent that issue.This will not be a fun
        //experience for whoever is trying to play the game, but at least it won’t freeze.
        if (frame_accumulator > desired_frame_time * 8)
        {
            resync = true;
        }

        //timer resync if requested
        //In my engine I have a manual callback I can use to “resync” my timer code(set the
        //accumulator to 0 and delta time to 1 / 60 the next time through the loop), which
        //I do after loading a level or swapping scenes.You need this because you typically
        //don’t want the game to start each level by immediately trying to make up the time it spent loading.
        if (resync)
        {
            frame_accumulator = 0;
            delta_time = desired_frame_time;
            resync = false;
        }

        //ProcessEvents(); //TODO process system events (Windows)
        ProcessInput();

        //fixed framerate, no interpolation, in other words, if the framerate drops, we still update the game logic
        //in a fixed number of steps. Reference: https://youtu.be/lW6ZtvQVzyg
        // TODO: review this as frame_accumulator starts as 0 it'll skip the UpdateLogic and render without updated transforms
        while (frame_accumulator >= desired_frame_time * update_multiplicity)
        {
            for (int i = 0; i < update_multiplicity; i++)
            {
                UpdateLogic(fixed_delta_time);
                frame_accumulator -= desired_frame_time;
            }
        }
        Render();
        //TODO: need to add a sdl_sleep here when !vsync && !frame_used_enough_time
    }
}

void Game::UpdateLogic( DeltaTime dt )
{
    UpdateTransforms();
    //TODO: Handle physics
    update_game_func( dt );
}

void Game::UpdateTransforms()
{
    ComponentUtils::ForEachInHierarchy( world, scene_root, [&]( entt::entity entity ) {
        entt::entity parent{ world.get<RelationshipComponent>(entity).parent };
        if (!world.valid( parent ) || !world.any_of<TransformComponent>(parent) || !world.any_of<TransformComponent>(entity))
        {
            return;
        }
        auto& parent_transform = world.get<TransformComponent>(parent);
        auto& transform = world.get<TransformComponent>(entity);
        transform.world_position.x = transform.position.x + parent_transform.world_position.x;
        transform.world_position.y = transform.position.y + parent_transform.world_position.y;
    });
}

void Game::Render()
{
    const Color& bg_color = game_info->bg_color;
    SDL_Renderer* sdl_renderer = renderer.get();
    SDL_SetRenderDrawColor(sdl_renderer, bg_color.R(), bg_color.G(), bg_color.B(), bg_color.A());
    SDL_RenderClear( sdl_renderer ); //clear back buffer

    ComponentUtils::ForEachInHierarchy( world, scene_root, [&]( entt::entity entity )
    {
        if ( world.all_of<TransformComponent, TextureComponent>(entity) )
        {
            RenderTexture(world.get<TextureComponent>(entity), world.get<TransformComponent>(entity));
        }
        if ( world.all_of<TransformComponent, RectangleComponent>(entity) )
        {
            RenderRectangle(world.get<RectangleComponent>(entity), world.get<TransformComponent>(entity));
        }
        if ( world.all_of<TransformComponent, LineComponent>(entity) )
        {
            RenderLine(world.get<LineComponent>(entity), world.get<TransformComponent>(entity));
        }
    });
    SDL_RenderPresent( sdl_renderer ); //swap front and back buffers
}

void Game::RenderTexture(
    const TextureComponent &texture_component, const TransformComponent &transform_component)
{
    SDL_Texture* sdl_texture = texture_component.texture.get();
    if (!sdl_texture || (!texture_component.is_visible))
    {
        return;
    }
    SDL_Rect dest;
    dest.w = Math::Round(transform_component.scale.x * (float) texture_component.width);
    dest.h = Math::Round(transform_component.scale.y * (float) texture_component.height);
    dest.x = Math::Round(transform_component.world_position.x);
    dest.y = Math::Round(transform_component.world_position.y);
    SDL_RenderCopyEx(
        renderer.get(),
        sdl_texture,
        nullptr,
        &dest,
        transform_component.rotation,
        nullptr,
        SDL_RendererFlip::SDL_FLIP_NONE
    );
}

void Game::RenderRectangle(const RectangleComponent& rect_component, const TransformComponent &transform_component)
{
    if (!rect_component.is_visible)
    {
        return;
    }
    SDL_SetRenderDrawColor(
        renderer.get(),
        rect_component.color.R(),
        rect_component.color.G(),
        rect_component.color.B(),
        rect_component.color.A()
    );
    SDL_Rect rect{
        rect_component.x + (int) transform_component.world_position.x,
        rect_component.y + (int) transform_component.world_position.y,
        (int) (rect_component.width * transform_component.scale.x),
        (int) (rect_component.height * transform_component.scale.y)
    };
    if (rect_component.is_filled)
    {
        SDL_RenderFillRect(renderer.get(), &rect);
    }
    else
    {
        SDL_RenderDrawRect(renderer.get(), &rect);
    }
}

void Game::RenderLine(const LineComponent& line_component, const TransformComponent &transform_component)
{
    if (!line_component.is_visible)
    {
        return;
    }
    SDL_SetRenderDrawColor(
        renderer.get(),
        line_component.color.R(),
        line_component.color.G(),
        line_component.color.B(),
        line_component.color.A()
    );
    SDL_RenderDrawLine(
        renderer.get(),
        transform_component.world_position.x + line_component.p1.x, //TODO apply scale and rotation
        transform_component.world_position.y + line_component.p1.y,
        transform_component.world_position.x + line_component.p2.x,
        transform_component.world_position.y + line_component.p2.y
    );
}

void Game::Quit()
{
    is_running = false;
}

entt::registry& Game::GetWorld()
{
    return world;
}

entt::entity Game::GetSceneRoot()
{
    return scene_root;
}

void Game::InitializeEntities()
{
    scene_root = world.create();
    auto& transform = world.emplace<TransformComponent>( scene_root );
    world.emplace<RelationshipComponent>( scene_root );
}

void Game::SetUpdateGameFunction( GameUpdateFunction update_game_func )
{
    this->update_game_func = update_game_func;
}

}