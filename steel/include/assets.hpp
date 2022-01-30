#pragma once

#include <string>

#include "components.hpp"
#include "steel_sdl.hpp"

namespace Steel
{
	class Assets
	{
	public:
        Assets();

        void SetRenderer(SDL_Renderer* renderer);
        TextureComponent LoadTexture(const std::string& filename);

	private:
        SDL_Renderer* renderer;
	};
}