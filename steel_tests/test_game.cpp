
#include <catch2/catch.hpp>
#include "steel.hpp"
#include <SDL.h>

TEST_CASE("test_game", "[test_game]") 
{
	Steel::Game *game = new Steel::Game();
	game->Start("Steel", 1280, 720, true);
	// simulate that "esc" was pressed to close the window:
	SDL_Event sdlevent;
	sdlevent.type = SDL_KEYDOWN;
	sdlevent.key.keysym.sym = SDLK_ESCAPE;
	SDL_PushEvent(&sdlevent);

	delete game;
}
