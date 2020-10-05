#include "./renderer.hpp"
#include <iostream>
#include <SDL_ttf.h>

#include "texture_component.hpp"
#include "actor.hpp"

namespace Steel
{
    
Renderer::Renderer(SharedPtr<ActorManager> actors)
    :
    window(nullptr),
    renderer(nullptr),
    game_info(CreateSharedPtr<GameInfo>()),
    actors(actors)
{}

void Renderer::Initialize(SharedPtr<GameInfo> game_info)
{
    this->game_info = game_info;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cerr << "Error initializing SDL." << std::endl;
        SDL_Quit();
		return; //TODO: consider throw exception
	}
	if (TTF_Init() != 0)
	{
		std::cerr << "Error initializing SDL TTF" << std::endl;
        SDL_Quit();
		return;
	}
	Uint32 sdlFlags = (
        game_info->IsWindowResizable() ? 
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE : SDL_WINDOW_SHOWN
    );
	window = SdlSharedPtr(
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
        SDL_Quit();
        return; //TODO: consider throw exception
	}
	renderer = SdlSharedPtr(
        SDL_CreateRenderer(window.get(), -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)
    );
	if (!renderer) 
    {
		std::cerr << "Error creating SDL renderer." << std::endl;
        SDL_Quit();
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
	
    // draw game objects:
    for (auto a : actors->GetAllActors())
    {
        if (!a->GetComponent<TextureComponent>().expired())
        {
            auto sdl_texture = a->GetComponent<TextureComponent>().
                lock()->GetTextureAsset()->GetTexture();
            if (sdl_texture != nullptr)
            {
                int w, h;
                SDL_QueryTexture(sdl_texture.get(), NULL, NULL, &w, &h);
                //TODO fill destination rectangle with actor->GetTransform() data
                SDL_Rect rect;
                rect.w = w;
                rect.h = h;
                rect.x = 0;
                rect.y = 0;
                SDL_RenderCopy(renderer.get(), sdl_texture.get(), 0, &rect);
            }
        }
    }

	//swap front and back buffers:
	SDL_RenderPresent(renderer.get());

}
SharedPtr<SDL_Renderer> Renderer::GetSDlRenderer()
{
    return this->renderer;
}


}