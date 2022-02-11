#pragma once

#include <string>
#include <unordered_map>

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

        TextureComponent GetText(const std::string& font_filename, int size, const std::string& text, const Color& color);
        TTF_Font* GetFont(const std::string& filename, int size);

	private:
        SDL_Renderer* renderer;
        std::unordered_map<std::string, SdlUniquePtr<TTF_Font>> fonts;
	};
}