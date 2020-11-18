#pragma once

#include <string>

#include "vector2.hpp"
#include "steel_sdl.hpp"

namespace Steel
{

typedef struct TransformComponent
{
    Vector2 position;
    Vector2 scale;
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
} TextureComponent;

// TODO SpriteComponent with animation (frames from a texture)

}