#pragma once

#include <SDL.h>
#include <string>

#include "core.hpp"
#include "game_info.hpp"

namespace Steel 
{
	class Renderer
	{
	private:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;

        SharedPtr<GameInfo> game_info;

	public:
		Renderer();

		void Initialize(SharedPtr<GameInfo> game_info);
		
		std::string GetWindowTitle();

		int GetWindowWidth();
		void SetWindowWidth(int value);
		
		int GetWindowHeight();
		void SetWindowHeight(int value);

		double GetDesiredFps();
		double GetTimeScale();

		void Render();

	};
}