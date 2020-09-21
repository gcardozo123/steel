#pragma once

#include <string>

#include "steel_sdl.hpp"
#include "core.hpp"

namespace Steel
{
class TextureAsset;


class AssetsContainer
{
private:
    SharedPtr<SDL_Renderer> renderer;

public:

    AssetsContainer(SharedPtr<SDL_Renderer> renderer);
    
    SharedPtr<TextureAsset> LoadTexture(std::string &filename);
	

};
}