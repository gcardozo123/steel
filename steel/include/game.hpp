#pragma once

#include "core.hpp"
#include "engine.hpp"

#include <string>

namespace Steel
{
	class Game
	{
	private:
		UniquePtr<Engine> engine;
        SharedPtr<GameInfo> game_info;

	public:
		Game();
		virtual ~Game();

		void Start(std::string window_title, int window_width, int window_height, bool is_window_resizable);
		void Quit();
	};
}