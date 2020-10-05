#include "game.hpp"
#include "log.hpp"


namespace Steel
{

Game::Game(){}
Game::~Game()
{}
	
void Game::Init(std::string window_title, int window_width, int window_height, bool is_window_resizable)
{   
}

void Game::Run()
{
}

void Game::Quit()
{
	//STEEL_CORE_ASSERT(engine, "Engine wasn't initialized, maybe you forgot to call game->Init();");
}

}