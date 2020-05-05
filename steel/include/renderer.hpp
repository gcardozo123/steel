#pragma once

#include <SDL.h>
#include <string>

#include "core.hpp"

namespace Steel 
{
	class Renderer
	{
	private:
		std::unique_ptr<SDL_Window, void(*)(SDL_Window*)> window;
		std::unique_ptr<SDL_Renderer, void(*)(SDL_Renderer*)> renderer;

		double desired_fps;
		double time_scale;

	public:
		Renderer();

		void Initialize(std::string window_title, int window_width, int window_height, bool is_window_resizable);
		
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