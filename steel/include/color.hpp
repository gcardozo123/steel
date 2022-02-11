#pragma once

#include "steel_math.hpp"

namespace Steel
{
class Color
{
public:
    Color() = default;
    ~Color() = default;
    ///RGBA values between [0, 255]
    Color(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
        :
        color(SDL_Color {r, g, b, a} )
    {}
    Color& operator=(const Color& c)
    {
        color.r = c.R();
        color.g = c.G();
        color.b = c.B();
        color.a = c.A();
        return *this;
    }

    uint8_t R() const { return color.r; }
    uint8_t G() const { return color.g; }
    uint8_t B() const { return color.b; }
    uint8_t A() const { return color.a; }

    void Set(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
    {
        color.r = r;
        color.g = g;
        color.b = b;
        color.a = a;
    }
    void SetR(uint8_t r) { color.r = r; }
    void SetG(uint8_t g) { color.g = g; }
    void SetB(uint8_t b) { color.b = b; }
    void SetA(uint8_t a) { color.a = a; }

    SDL_Color ToSdl() const { return SDL_Color {color.r, color.g, color.b, color.a}; }

private:
    SDL_Color color;
}; //Color

} //Steel
