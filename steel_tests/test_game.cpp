
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
    game.Init("Potato game", window_width, window_height, Steel::Color(199, 199, 199, 255), true, 120.0f);

    std::string filename = "game_assets/ghost1.png";
    auto texture_component = game.GetAssets().LoadTexture(filename);
    auto world = game.GetWorld();
    
    // Create entities:
    VelocityComponent velocity {Math::Vector2(0.0f, 1.0f), 100.0f };
    auto& ghost_entity = world->entity("Ghost")
        .set<TextureComponent>(texture_component)
        .set<TransformComponent>(TransformComponent())
        .set<VelocityComponent>(velocity);

    auto& move_system = world->system<TransformComponent , const VelocityComponent>("MoveSystem").each(MoveSystemFunc);

    Color c{3, 252, 227, 255};
    RectangleComponent rect_comp{0.f, 0.f, 128.f, 128.f, c, false};
    auto& r1 = world->entity("r1")
        .set<RectangleComponent>(rect_comp);

    //TODO: handle hierarchies: ghost_entity.set<RectangleComponent>(rect_comp);

    Math::Vector2 p1 {100.f, 100.f};
    Math::Vector2 p2 {200.f, 200.f};
    LineComponent line_comp {p1, p2, c};
    auto& l1 = world->entity("l1")
        .set<LineComponent>(line_comp);

    game.Run();
}