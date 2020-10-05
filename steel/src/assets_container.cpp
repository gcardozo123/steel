#include "./assets_container.hpp"
#include "texture_asset.hpp"

namespace Steel
{

AssetsContainer::AssetsContainer(SharedPtr<SDL_Renderer> renderer)
    :
    renderer(renderer)
{}

SharedPtr<TextureAsset> AssetsContainer::LoadTexture(std::string &filename)
{
    auto texture = CreateSharedPtr<TextureAsset>(renderer);
    texture->Load(filename);
    return texture;
}

}