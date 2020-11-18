#include "assets.hpp"

namespace Steel
{

Assets::Assets(SharedPtr<SDL_Renderer> renderer)
    :
    renderer(renderer)
{
}

void Assets::SetRenderer(SharedPtr<SDL_Renderer> renderer)
{
    this->renderer = renderer;
}

TextureComponent Assets::LoadTexture(std::string & filename)
{
    TextureComponent texture_component;
    
    texture_component.filename = filename;
    SDL_Surface *surface = IMG_Load(filename.c_str());
    texture_component.texture = SdlSharedPtr(
        SDL_CreateTextureFromSurface(renderer.get(), surface)
    );
    SDL_FreeSurface(surface);
    
    return texture_component;
}



}