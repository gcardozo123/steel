#pragma once

#include <string>

#include "core.hpp"
#include "engine.hpp"
#include "assets_container.hpp"
#include "actor_manager.hpp"

namespace Steel
{

class Game
{

private:
	UniquePtr<Engine> engine;
    SharedPtr<GameInfo> game_info;

public:
    SharedPtr<AssetsContainer> assets;
    SharedPtr<ActorManager> actors;
    //SharedPtr<Scene> scene;

public:
	Game();
	virtual ~Game();

	void Init(std::string window_title, int window_width, int window_height, bool is_window_resizable);
    void Run();
    void Quit();
};

}