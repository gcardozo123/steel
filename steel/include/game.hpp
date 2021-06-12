#pragma once

#include <string>

#include "assets.hpp"
#include "core.hpp"
#include "steel_sdl.hpp"

namespace Steel
{
class GameInfo;

class Game
{
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
    void Run();
    void Quit();

    /**
     * @brief Returns the `flecs::world` used by Steel
     */
//    SharedPtr<flecs::world> GetWorld();
    /**
     * @brief Returns the `flecs::entity` to be used as root of your scene.
     *
     * Steel will always assume `GetSceneRoot` is the scene root. Make sure you don't
     * change that.
     */
//    SharedPtr<flecs::entity> GetSceneRoot();
    Assets& GetAssets() { return assets; }

private:
//    SharedPtr<flecs::world> world;
//    SharedPtr<flecs::entity> scene_root;
    bool is_running;
    SharedPtr<GameInfo> game_info;

    //Rendering:
    SharedPtr<SDL_Window> window;
    SharedPtr<SDL_Renderer> renderer;

    Assets assets;

    void InitializeRenderer();
    void RegisterComponents();
    void ProcessInput();
    void UpdateLogic(double dt);
    void Render();

    void UpdateTransforms(TransformComponent &transform_component);
    void RenderTexture(
        TextureComponent& texture_component, const TransformComponent& transform_component
    );
    void RenderRectangle(RectangleComponent& rect_component, const TransformComponent &transform_component);
    void RenderLine(LineComponent& line_component, const TransformComponent &transform_component);
};

}