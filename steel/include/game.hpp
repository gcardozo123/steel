#pragma once

#include <string>

#include <entt.hpp>

#include "assets.hpp"
#include "core.hpp"
#include "steel_sdl.hpp"

namespace Steel
{
struct GameInfo;

class Game
{
    using GameUpdateFunction = std::function<void (DeltaTime)>;

public:
    explicit Game(const GameInfo* game_info);
    virtual ~Game();

    void Init();
    void SetUpdateGameFunction( GameUpdateFunction update_game_func );
    void Run();
    void Quit();

    /**
     * @brief Returns the `entt::registry` used by Steel
     */
    entt::registry& GetWorld();
    /**
     * @brief Returns the `entt::entity` to be used as root of your scene.
     *
     * Steel will always assume `GetSceneRoot` is the scene root. Make sure you don't
     * change that.
     */
    entt::entity GetSceneRoot();
    Assets& GetAssets() { return assets; }

private:
    entt::registry world;
    entt::entity scene_root;

    bool is_running;
    const GameInfo* game_info;

    //Rendering:
    SharedPtr<SDL_Window> window;
    SharedPtr<SDL_Renderer> renderer;

    Assets assets;

    GameUpdateFunction update_game_func;

    void InitializeRenderer();
    void InitializeEntities();
    void ProcessInput();
    void UpdateLogic(DeltaTime dt);
    void Render();

    void UpdateTransforms();
    void RenderTexture(
        TextureComponent& texture_component, const TransformComponent& transform_component
    );
    void RenderRectangle(RectangleComponent& rect_component, const TransformComponent &transform_component);
    void RenderLine(LineComponent& line_component, const TransformComponent &transform_component);
};

}