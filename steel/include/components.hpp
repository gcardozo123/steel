#pragma once

#include <string>

#include <entt.hpp>
#include <utility>

#include "vector2.hpp"
#include "steel_sdl.hpp"
#include "color.hpp"

namespace Steel
{

struct RelationshipComponent
{
    entt::entity first_child{entt::null};
    entt::entity prev_sibling{entt::null};
    entt::entity next_sibling{entt::null};
    entt::entity parent{entt::null};
};

struct TransformComponent
{
    Math::Vector2 position;
    Math::Vector2 world_position;
    Math::Vector2 scale;
    double rotation;    // in degrees
    TransformComponent()
        :
        scale(1.0, 1.0),
        rotation(0)
    {}
};

struct VelocityComponent
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
};

struct TextureComponent
{
    SdlUniquePtr<SDL_Texture> texture;
    int width{};
    int height{};
    bool is_visible = false;
    TextureComponent() = default;
    TextureComponent(SDL_Texture* sdl_texture, const int width, const int height, const bool is_visible=true)
        :
        texture(SdlMakeUniquePtr(sdl_texture)),
        width(width),
        height(height),
        is_visible(is_visible)
    {}
    TextureComponent(const TextureComponent& ) = delete;
    TextureComponent& operator=(const TextureComponent& ) = delete;

    TextureComponent(TextureComponent &&other) noexcept { *this = std::move(other); }
    TextureComponent& operator=(TextureComponent &&other) noexcept
    {
        texture = std::move(other.texture);
        width = other.width;
        height = other.height;
        is_visible = other.is_visible;
        other.width = 0;
        other.height = 0;
        other.is_visible = false;
        return *this;
    }
};

struct LineComponent
{
    Math::Vector2 p1;
    Math::Vector2 p2;
    Color color; // defaults to blue
    bool is_visible;
    LineComponent()
        :
        p1(Math::Vector2()),
        p2(Math::Vector2()),
        color(52, 195, 235, 255),
        is_visible(true)
    {}
    LineComponent(Math::Vector2& p1, Math::Vector2& p2, Color& c)
        :
        p1(p1),
        p2(p2),
        color(c),
        is_visible(true)
    {}
};

struct RectangleComponent
{
    float x;
    float y;
    float width;
    float height;
    Color color; // defaults to green
    bool is_filled; //if `true` renders a filled rectangle
    bool is_visible; // defaults to `true`
    RectangleComponent()
        :
        x(0.f), y(0.f), width(0.f), height(0.f), color(52, 235, 55, 255), is_filled(false), is_visible(true)
    {}
    RectangleComponent(float x, float y, float width, float height, Color& c, bool is_filled = false)
        :
        x(x), y(y), width(width), height(height), color(c), is_filled(is_filled), is_visible(true)
    {}
};

}