
#include <string>

#include <catch2/catch.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "steel.hpp"

using namespace Steel;

TEST_CASE("test_game", "[test_game]")
{
    Game game;
    game.Init("Potato game", 1280, 720, true);

    auto texture_component = game.GetAssets().LoadTexture(std::string("game_assets/ghost1.png"));
    auto world = game.GetWorld();
    
    // Create entities:
    world->entity("Ghost")
        .set<TextureComponent>(texture_component)
        .set<TransformComponent>(TransformComponent());

    auto other_transform = TransformComponent();
    other_transform.position.Set(200.0, 200.0);
    other_transform.scale.x = 0.5;
    other_transform.scale.y = 2;

    world->entity("Other Ghost")
        .set<TextureComponent>(texture_component)
        .set<TransformComponent>(other_transform);

    game.Run();
}