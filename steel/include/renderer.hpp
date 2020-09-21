#pragma once

#include <string>

#include "core.hpp"
#include "game_info.hpp"
#include "steel_sdl.hpp"
#include "actor_manager.hpp"

namespace Steel 
{

class Renderer
{
private:
    SharedPtr<SDL_Window> window;
    SharedPtr<SDL_Renderer> renderer;
    SharedPtr<GameInfo> game_info;
    SharedPtr<ActorManager> actors;

public:
	Renderer(SharedPtr<ActorManager> actors);
    ~Renderer() = default;

	void Initialize(SharedPtr<GameInfo> game_info);
		
	std::string GetWindowTitle();

	int GetWindowWidth();
	void SetWindowWidth(int value);
		
	int GetWindowHeight();
	void SetWindowHeight(int value);

	double GetDesiredFps();
	double GetTimeScale();

	void Render();

    SharedPtr<SDL_Renderer> GetSDlRenderer();
};


}