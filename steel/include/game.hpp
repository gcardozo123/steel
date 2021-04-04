#pragma once

#include <string>

#include "flecs.h"

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

    void Init(std::string window_title, int window_width, int window_height, bool is_window_resizable);
    void Run();
    void Quit();

    SharedPtr<flecs::world> GetWorld();
    Assets& GetAssets() { return assets; }

private:
    SharedPtr<flecs::world> world;
    bool is_running;
    SharedPtr<GameInfo> game_info;

    //Rendering:
    SharedPtr<SDL_Window> window;
    SharedPtr<SDL_Renderer> renderer;

    Assets assets;

    void InitializeRenderer();
    void RegisterComponents();
    void ProcessInput();
    void Render();
};

}