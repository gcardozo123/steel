#pragma once

#include "core.hpp"
#include "game_info.hpp"
#include "renderer.hpp"
#include "actor_manager.hpp"

namespace Steel
{

class Engine
{
    friend class Game;

private:
	bool is_running;
	SharedPtr<GameInfo> game_info;
	SharedPtr<Renderer> renderer;
    SharedPtr<ActorManager> actors;
		
	/*
	Physics physics;
	ProcessManager process_manager;
	InputManager input_manager;*/

public:
	Engine();
		
	void Init(SharedPtr<GameInfo> game_info);
	void Stop();

    SharedPtr<Renderer> GetRenderer() { return this->renderer; }
    void SetActors(SharedPtr<ActorManager> actors);
	
    void RunMainLoop();

private:	
	void ProcessInput();
};

}