#include "game.hpp"

#include "log.hpp"

namespace Steel
{

Game::Game()
	: 
    engine(CreateUniquePtr<Engine>()),
    game_info(CreateSharedPtr<GameInfo>()),
    assets(nullptr),
    actors(CreateSharedPtr<ActorManager>())
{}
Game::~Game()
{}
	
void Game::Init(std::string window_title, int window_width, int window_height, bool is_window_resizable)
{
    this->game_info->SetDesiredFps(60.0f);
    this->game_info->SetWindowWidth(window_width);
    this->game_info->SetWindowHeight(window_height);
    this->game_info->SetWindowResizable(is_window_resizable);
    this->game_info->SetWindowTitle(window_title);
    this->game_info->SetTimeScale(1.0);

    engine->SetActors(this->actors);
    engine->Init(this->game_info);
    assets = CreateSharedPtr<AssetsContainer>(engine->GetRenderer()->GetSDlRenderer());
}

void Game::Run()
{
    engine->RunMainLoop();
}

void Game::Quit()
{
	STEEL_CORE_ASSERT(engine, "Engine wasn't initialized, maybe you forgot to call game->Init();");
	engine->Stop();
}

}