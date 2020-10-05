#pragma once

#include <string>

#include "core.hpp"


namespace Steel
{

class Game
{

public:
	Game();
	virtual ~Game();

	void Init(std::string window_title, int window_width, int window_height, bool is_window_resizable);
    void Run();
    void Quit();
};

}