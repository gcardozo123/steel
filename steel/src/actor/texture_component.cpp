#include "./texture_component.hpp"

namespace Steel
{

TextureComponent::TextureComponent(StrongActorPtr owner)
    :
    ActorComponent(owner, ActorComponentId(typeid(this))),
    texture_asset(nullptr)
{}

SharedPtr<TextureAsset> TextureComponent::GetTextureAsset()
{
    return this->texture_asset;
}

void TextureComponent::SetTextureAsset(SharedPtr<TextureAsset> texture_asset)
{
    this->texture_asset = texture_asset;
}

}