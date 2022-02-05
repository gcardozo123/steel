#include "assets.hpp"
#include "asserts.hpp"

namespace Steel
{

Assets::Assets()
    :
    renderer(nullptr)
{
}

void Assets::SetRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

TextureComponent Assets::LoadTexture(const std::string& filename)
{
    if (!renderer)
    {
        STEEL_CORE_ASSERT(false, "Missing renderer for Assets to work with");
        return {};
    }
    SDL_Surface *surface = IMG_Load(filename.c_str());
    TextureComponent res{SDL_CreateTextureFromSurface(renderer, surface), surface->w, surface->h};
    SDL_FreeSurface(surface);
    return res;
}

}