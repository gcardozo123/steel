#pragma once

#include <string>

#include "components.hpp"
#include "steel_sdl.hpp"

namespace Steel
{
	class Assets
	{
	private:
        SharedPtr<SDL_Renderer> renderer;

	public:

        Assets(SharedPtr<SDL_Renderer> renderer);

        /*
        Assets needs a `SDL_Renderer` because `SDL` relies on 
        it when loading assets.
        */
        void SetRenderer(SharedPtr<SDL_Renderer> renderer);
        
        TextureComponent LoadTexture(std::string &filename);
	};
}