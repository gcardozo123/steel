
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
    p.x += (direction.x * velocity.scale); //* dt;
    p.y += (direction.y * velocity.scale); //* dt;
    //printf("Dt: %f\n", dt);
}

void GameUpdate( Steel::DeltaTime dt, entt::registry& world )
{
    auto view = world.view<VelocityComponent, TransformComponent>();
    view.each( [&]( auto& velocity, auto& transform ) { MoveSystemFunc( transform, velocity, dt ); } );
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
    game.SetUpdateGameFunction( [&]( Steel::DeltaTime dt ) { GameUpdate( dt, world ); } );

    // Create entities:
    std::string filename = "game_assets/ghost1.png";
    entt::entity ghost = ComponentUtils::AddChild( world, game.GetSceneRoot() );
    TextureComponent& ghost_texture = world.emplace<TextureComponent>(ghost, game.GetAssets().LoadTexture(filename));
    //ghost_texture.is_visible = false;
    world.emplace<VelocityComponent>(ghost, Math::Vector2(1.0f, 1.0f), 0.1f);

    auto& transform = world.get<TransformComponent>(ghost);
    transform.scale.Set(0.75, 0.75);
    transform.position.x = 100;
    transform.position.y = 200;

    for (int i = 0; i < 3; i++)
    {
        entt::entity child = ComponentUtils::AddChild( world, ghost );
        world.emplace<TextureComponent>( child, game.GetAssets().LoadTexture(filename) );

        auto& child_transform = world.get<TransformComponent>( child );
        child_transform.position.x = child_transform.position.y = (float(i) + 1) * 20;
    }
    game.Run();
}