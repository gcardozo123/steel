#pragma once

#include <SDL.h>
#include <string>

#include "core.hpp"

namespace Steel
{

class TextureAsset
{
private:
    std::string filename;
    SharedPtr<SDL_Renderer> renderer;
    SharedPtr<SDL_Texture> texture;


public:
    TextureAsset(SharedPtr<SDL_Renderer> renderer);

    SharedPtr<SDL_Texture> Load(std::string &filename);
    SharedPtr<SDL_Texture> GetTexture();
};

}