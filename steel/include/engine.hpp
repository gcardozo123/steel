#pragma once

#include "core.hpp"
#include "game_info.hpp"
#include "renderer.hpp"

namespace Steel
{
	class Engine
	{
	private:
		bool is_running;
		SharedPtr<GameInfo> game_info;
		SharedPtr<Renderer> renderer;
		
		/*
		Physics physics;
		ProcessManager process_manager;
		InputManager input_manager;*/

	public:
		Engine();
		
		void Start(std::string window_title, int window_width, int window_height, bool is_window_resizable);
		void Stop();
		
	private:
		void RunMainLoop();
		void ProcessInput();
	};
}