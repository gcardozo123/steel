
#include <string>

#include <catch2/catch.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "steel.hpp"

using namespace Steel;

TEST_CASE("test_game", "[test_game]")
{
    Game game;
    float window_width = 1280, window_height = 720;
    game.Init("Potato game", window_width, window_height, true);

    std::string filename = "game_assets/ghost1.png";
    auto texture_component = game.GetAssets().LoadTexture(filename);
    auto world = game.GetWorld();
    
    // Create entities:
    world->entity("Ghost")
        .set<TextureComponent>(texture_component)
        .set<TransformComponent>(TransformComponent());

    auto other_transform = TransformComponent();
    other_transform.scale.Set(2, 3);
    other_transform.position.Set(
        window_width - texture_component.width * other_transform.scale.x,
        window_height - texture_component.height * other_transform.scale.y
    );

    world->entity("Other Ghost")
        .set<TextureComponent>(texture_component)
        .set<TransformComponent>(other_transform);

    game.Run();
}