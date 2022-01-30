#include "assets.hpp"
#include "log.hpp"

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
    TextureComponent res;
    if (!renderer)
    {
        STEEL_CORE_ERROR("Missing renderer for Assets to work with");
        return res;
    }
    SDL_Surface *surface = IMG_Load(filename.c_str());
    res.texture = SdlMakeUniquePtr(
        SDL_CreateTextureFromSurface(renderer, surface)
    );
    res.width = (float) surface->w;
    res.height = (float) surface->h;
    SDL_FreeSurface(surface);
    
    return res;
}

}