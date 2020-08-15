#include "./renderer.hpp"
#include <iostream>
#include <SDL_ttf.h>

namespace Steel
{
    Renderer::Renderer()
        :
        window(nullptr, SDL_DestroyWindow),
        renderer(nullptr, SDL_DestroyRenderer),
        game_info(CreateSharedPtr<GameInfo>())
    {}

	void Renderer::Initialize(SharedPtr<GameInfo> game_info)
	{
        this->game_info = game_info;
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			std::cerr << "Error initializing SDL." << std::endl;
			return; //TODO: consider throw exception
		}
		if (TTF_Init() != 0)
		{
			std::cerr << "Error initializing SDL TTF" << std::endl;
			return;
		}
		Uint32 sdlFlags = (
            game_info->IsWindowResizable() ? 
            SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE : SDL_WINDOW_SHOWN
        );
		window.reset(
			SDL_CreateWindow(
				game_info->GetWindowTitle().c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				game_info->GetWindowWidth(),
                game_info->GetWindowHeight(),
				sdlFlags
			)
		);
		if (!window)
		{
			std::cerr << "Error creating SDL window." << std::endl;
			return; //TODO: consider throw exception
		}

		renderer.reset(SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC));
		if (!renderer) {
			std::cerr << "Error creating SDL renderer." << std::endl;
			return; //TODO: consider throw exception
		}
	}

	std::string Renderer::GetWindowTitle()
	{
		return std::string(SDL_GetWindowTitle(window.get()));
	}

	int Renderer::GetWindowWidth()
	{
		if (!window)
			return 0;
		
		int x, y;
		SDL_GetWindowSize(window.get(), &x, &y);
		return x;
	}

	void Renderer::SetWindowWidth(int value)
	{
        game_info->SetWindowWidth(value);
        SDL_SetWindowSize(window.get(), value, GetWindowHeight());
	}

	int Renderer::GetWindowHeight()
	{
		if (!window)
			return 0;
		
		int x, y;
		SDL_GetWindowSize(window.get(), &x, &y);
		return y;
	}

	void Renderer::SetWindowHeight(int value)
	{
        game_info->SetWindowHeight(value);
        SDL_SetWindowSize(window.get(), GetWindowWidth(), value);
	}

	double Renderer::GetDesiredFps()
	{
		return game_info->GetDesiredFps();
	}
	
	double Renderer::GetTimeScale()
	{
		return game_info->GetTimeScale();
	}
	
	void Renderer::Render()
	{
		//set background color:
		SDL_SetRenderDrawColor(renderer.get(), 50, 50, 80, 255);
		//clear back buffer:
		SDL_RenderClear(renderer.get());
		//todo: draw game objects

		//swap front and back buffers:
		SDL_RenderPresent(renderer.get());

	}
}