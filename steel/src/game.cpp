#include "game.hpp"
#include "log.hpp"

namespace Steel
{
	Game::Game()
		: engine(nullptr)
	{
	}
	Game::~Game()
	{
	}
	
	void Game::Start(std::string window_title, int window_width, int window_height, bool is_window_resizable)
	{
		engine = CreateUniquePtr<Engine>();
		engine->Start(window_title, window_width, window_height, is_window_resizable);
	}
	
	void Game::Quit()
	{
		STEEL_CORE_ASSERT(engine, "Engine wasn't initialized, maybe you forgot to call game->Start();");
		engine->Stop();
	}
}