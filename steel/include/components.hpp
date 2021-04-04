#pragma once

#include <string>

#include "vector2.hpp"
#include "steel_sdl.hpp"

namespace Steel
{

typedef struct TransformComponent
{
    Math::Vector2 position;
    Math::Vector2 scale;
    double rotation;

    TransformComponent()
        :
        scale(1.0, 1.0),
        rotation(0)
    {}
} TransformComponent;

typedef struct TextureComponent
{
    std::string filename;
    SharedPtr<SDL_Texture> texture;
    float width = 0, height = 0;
} TextureComponent;

// TODO SpriteComponent with animation (frames from a texture)

}