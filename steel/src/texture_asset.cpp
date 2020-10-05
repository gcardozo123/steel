#include "./texture_asset.hpp"

#include "steel_sdl.hpp"

namespace Steel
{

TextureAsset::TextureAsset(SharedPtr<SDL_Renderer> renderer)
    :
    filename(""),
    renderer(renderer),
    texture(nullptr)
{}

SharedPtr<SDL_Texture> TextureAsset::Load(std::string &filename)
{
    this->filename = filename;
    SDL_Surface *surface = IMG_Load(filename.c_str());
    this->texture = SdlSharedPtr(
        SDL_CreateTextureFromSurface(renderer.get(), surface)
    );
    SDL_FreeSurface(surface);
    return this->texture;
}

SharedPtr<SDL_Texture> TextureAsset::GetTexture()
{
    return this->texture;
}

}