
#include <string>
#include <functional>

#include <catch2/catch.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "steel.hpp"

using namespace Steel;

void MoveSystemFunc( TransformComponent& transform, const VelocityComponent& velocity, Steel::DeltaTime dt )
{
    Math::Vector2& p = transform.position;
    const Math::Vector2& direction = velocity.direction;
    p.x += (direction.x * velocity.scale) * dt;
    //p.y += (direction.y * velocity.scale) * dt;
    //printf("Dt: %f, PX: %f, PY: %f\n", dt, p.x, p.y);
}

TEST_CASE( "test_game", "[test_game]" )
{
    Game game;
    float window_width = 1280, window_height = 720;
    game.Init(
        "Potato game",
        window_width,
        window_height,
        Steel::Color(199, 199, 199, 255),
        true,
        60.0f
    );

    auto& world = game.GetWorld();

    // Create entities:
    std::string filename = "game_assets/ghost1.png";
    entt::entity ghost = ComponentUtils::AddChild( world, game.GetSceneRoot() );
    TextureComponent& ghost_texture = world.emplace<TextureComponent>(ghost, game.GetAssets().LoadTexture(filename));
    //ghost_texture.is_visible = false;
    world.emplace<VelocityComponent>(ghost, Math::Vector2(1.0f, 1.0f), 10.0f);

    auto& transform = world.get<TransformComponent>(ghost);
    transform.scale.Set(0.75, 0.75);
    transform.position.x = 100;
    transform.position.y = 200;

    for (int i = 0; i < 4; i++)
    {
        entt::entity child = ComponentUtils::AddChild( world, ghost );
        world.emplace<TextureComponent>( child, game.GetAssets().LoadTexture(filename) );

        auto& child_transform = world.get<TransformComponent>( child );
        if ( i == 2 )
        {
            child_transform.position.x = 200.0f;
        }
        else
        {
            child_transform.position.x = child_transform.position.y = (float(i) + 1) * 20;
        }
    }

    entt::entity child2 = ComponentUtils::GetChild(world, ghost, 2);
    entt::entity child2_child = ComponentUtils::AddChild( world, child2 );
    world.emplace<TextureComponent>( child2_child, game.GetAssets().LoadTexture(filename) );
    auto& child2_child_transform = world.get<TransformComponent>( child2_child );
    child2_child_transform.scale.Set (0.5f, 0.5f);
    child2_child_transform.position.x = 64.0f * 3.0f;
    child2_child_transform.position.y = 32.0f;

    float angle = 0.0f;
    game.SetUpdateGameFunction( [&]( Steel::DeltaTime dt ) {
        auto view = world.view<VelocityComponent, TransformComponent>();
        view.each( [&]( auto& velocity, auto& transform ) { MoveSystemFunc( transform, velocity, dt ); } );

        child2_child_transform.position = Steel::Math::Vector2(64.f * 3, 32.f).Rotated(angle);
        angle -= 3.f;
    } );

    game.Run();
}