#pragma once

#include "vector4.hpp"

namespace Steel
{
class Color
{
public:
    Color() = default;
    ~Color() = default;
    //RGBA values should be between [0, 255]
    Color(float r, float g, float b, float a)
        :
        color(
            Math::Clamp(r, 0.f, 255.f),
            Math::Clamp(g, 0.f, 255.f),
            Math::Clamp(b, 0.f, 255.f),
            Math::Clamp(a, 0.f, 255.f)
        ){}
    Color& operator=(const Color& c)
    {
        color.r = c.r();
        color.g = c.g();
        color.b = c.b();
        color.a = c.a();
        return *this;
    }

    float r() const { return color.r; }
    float g() const { return color.g; }
    float b() const { return color.b; }
    float a() const { return color.a; }

    void Set(float r, float g, float b, float a)
    {
        color.r = Math::Clamp(r, 0.f, 255.f);
        color.g = Math::Clamp(g, 0.f, 255.f);
        color.b = Math::Clamp(b, 0.f, 255.f);
        color.a = Math::Clamp(a, 0.f, 255.f);
    }
    void SetR(float r) { color.r = Math::Clamp(r, 0.f, 255.f); }
    void SetG(float g) { color.g = Math::Clamp(g, 0.f, 255.f); }
    void SetB(float b) { color.b = Math::Clamp(b, 0.f, 255.f); }
    void SetA(float a) { color.a = Math::Clamp(a, 0.f, 255.f); }

private:
    Math::Vector4 color;
}; //Color

} //Steel
