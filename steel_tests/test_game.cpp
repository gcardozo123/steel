
#include <string>
#include <functional>

#include <catch2/catch.hpp>
#include <SDL.h>
#include <SDL_image.h>

#include "steel.hpp"

using namespace Steel;

TEST_CASE("test_game", "[test_game]")
{
    Game game;
    float window_width = 1280, window_height = 720;
    game.Init(
        "Potato game",
        window_width,
        window_height,
        Steel::Color(199, 199, 199, 255),
        true,
        120.0f
    );

    auto& world = game.GetWorld();

    // Create entities:
    std::string filename = "game_assets/ghost1.png";
    entt::entity ghost = world.create();

    auto& root_children = world.get<ChildrenComponent>(game.GetSceneRoot());
    root_children.num_children = 1;
    root_children.children[0] = ghost;

    auto& transform = world.emplace<TransformComponent>(ghost);
    transform.scale.Set(0.75, 0.75);
    transform.position.x = 100;
    transform.position.y = 200;
    ChildrenComponent& ghost_children_component = world.emplace<ChildrenComponent>(ghost);
    ghost_children_component.num_children = 3;

    ParentComponent parent_component = world.emplace<ParentComponent>(ghost);
    parent_component.parent = game.GetSceneRoot();

    world.emplace<TextureComponent>(ghost, game.GetAssets().LoadTexture(filename));
    world.emplace<VelocityComponent>(ghost, Math::Vector2(1.0f, 1.0f), 1.0f);

    for (int i = 0; i < 3; i++)
    {
        entt::entity child = world.create();
        auto &child_transform = world.emplace<TransformComponent>(child);
        child_transform.position.x = child_transform.position.y = (float(i) + 1) * 20;

        ChildrenComponent& grandchildren = world.emplace<ChildrenComponent>(child);
        grandchildren.num_children = 0;
        ParentComponent parent = world.emplace<ParentComponent>(child);
        parent.parent = ghost;

        world.emplace<TextureComponent>(child, game.GetAssets().LoadTexture(filename));
        ghost_children_component.children[i] = entt::entity(child);
    }
    game.Run();
}