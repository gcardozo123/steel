
#include <string>
#include <functional>

#include <catch2/catch.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "steel.hpp"

using namespace Steel;

void MoveSystemFunc(flecs::entity e, TransformComponent& transform, const VelocityComponent& velocity)
{
    Math::Vector2& p = transform.position;
    const Math::Vector2& direction = velocity.direction;
    p.x += (direction.x * velocity.scale) * e.delta_time();
    p.y += (direction.y * velocity.scale) * e.delta_time();
}

TEST_CASE("test_game", "[test_game]")
{
    Game game;
    float window_width = 1280, window_height = 720;
    game.Init("Potato game", window_width, window_height, true, 120.0f);

    std::string filename = "game_assets/ghost1.png";
    auto texture_component = game.GetAssets().LoadTexture(filename);
    auto world = game.GetWorld();
    
    // Create entities:
    VelocityComponent velocity {Math::Vector2(0.0f, 1.0f), 100.0f };
    auto& ghost_entity = world->entity("Ghost")
        .set<TextureComponent>(texture_component)
        .set<TransformComponent>(TransformComponent())
        .set<VelocityComponent>(velocity);

    auto& move_system = world->system<TransformComponent , const VelocityComponent>("MoveSystem").each(
        std::bind(MoveSystemFunc, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3)
    );
    game.Run();
}