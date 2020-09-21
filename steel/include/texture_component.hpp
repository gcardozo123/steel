#pragma once

#include "core.hpp"
#include "texture_asset.hpp"
#include "actor_component.hpp"

namespace Steel
{

class TextureComponent : public ActorComponent
{
private:
    SharedPtr<TextureAsset> texture_asset;


public:
    TextureComponent(StrongActorPtr owner);

    SharedPtr<TextureAsset> GetTextureAsset();
    void SetTextureAsset(SharedPtr<TextureAsset> texture_asset);
};

}