#pragma once

#include <string>

#include <entt.hpp>

#include "assets.hpp"
#include "core.hpp"
#include "steel_sdl.hpp"

namespace Steel
{
class GameInfo;

class Game
{
    using GameUpdateFunction = std::function<void (DeltaTime)>;
    enum class RenderingMode
    {
        PixelPerfect,
        Default,
    };

public:
    Game();
    virtual ~Game();

    void Init(
        std::string window_title,
        int window_width,
        int window_height,
        Steel::Color background_color,
        bool is_window_resizable,
        float desired_fps
    );
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
//    entt::entity hud;
    /// Root of all gameplay menus, to be used for inventories and other menus you access during the gameplay loop.
//    entt::entity in_game_menus;
    /// Root of all menus that are not part of the gameplay: pause menu, options, etc.
//    entt::entity menus;

    bool is_running;
    RenderingMode rendering_mode = RenderingMode::PixelPerfect;
    SharedPtr<GameInfo> game_info;

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