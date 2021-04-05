#pragma once

#include <string>

#include "vector2.hpp"
#include "steel_sdl.hpp"
#include "color.hpp"

namespace Steel
{

typedef struct TransformComponent
{
    Math::Vector2 position;
    Math::Vector2 scale;
    double rotation;    // in degrees
    TransformComponent()
        :
        scale(1.0, 1.0),
        rotation(0)
    {}
} TransformComponent;

typedef struct VelocityComponent
{
    Math::Vector2 direction;
    float scale;
    VelocityComponent()
        :
        direction(0.0f, 0.0f),
        scale(0.0f)
    {}
    VelocityComponent(const Math::Vector2& direction, float scale)
        :
        direction(direction),
        scale(scale)
    {}
} VelocityComponent;

typedef struct TextureComponent
{
    std::string filename;
    SharedPtr<SDL_Texture> texture;
    float width;
    float height = 0;
    TextureComponent()
        :
        filename(""),
        texture(nullptr),
        width(0.0f),
        height(0.0f)
    {}
} TextureComponent;

typedef struct LineComponent
{
    Math::Vector2 p1;
    Math::Vector2 p2;
    Color color; // defaults to blue
    LineComponent()
        :
        p1(Math::Vector2()),
        p2(Math::Vector2()),
        color(52, 195, 235, 255)
    {}
    LineComponent(Math::Vector2& p1, Math::Vector2& p2, Color& c)
        :
        p1(p1),
        p2(p2),
        color(c)
    {}
} LineComponent;

typedef struct RectangleComponent
{
    float x;
    float y;
    float width;
    float height;
    Color color; // defaults to green
    bool is_filled; //if `true` renders a filled rectangle
    RectangleComponent()
        :
        x(0.f), y(0.f), width(0.f), height(0.f), color(52, 235, 55, 255), is_filled(false)
    {}
    RectangleComponent(float x, float y, float width, float height, Color& c, bool is_filled = false)
        :
        x(x), y(y), width(width), height(height), color(c), is_filled(is_filled)
    {}
} RectangleComponent;

}