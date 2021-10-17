#include "assets.hpp"

#include <utility>

namespace Steel
{

Assets::Assets(SharedPtr<SDL_Renderer> renderer)
    :
    renderer(std::move(renderer))
{
}

void Assets::SetRenderer(SharedPtr<SDL_Renderer> renderer)
{
    this->renderer = renderer;
}

TextureComponent Assets::LoadTexture(const std::string& filename)
{
    TextureComponent texture_component;
    
    texture_component.filename = filename;
    SDL_Surface *surface = IMG_Load(filename.c_str());
    texture_component.texture = SdlSharedPtr(
        SDL_CreateTextureFromSurface(renderer.get(), surface)
    );
    texture_component.width = (float) surface->w;
    texture_component.height = (float) surface->h;
    SDL_FreeSurface(surface);
    
    return texture_component;
}

}