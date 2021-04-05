#pragma once

namespace Steel
{
namespace Math
{
class Vector4
{
public:
    union { float x; float width; float r; };
    union { float y; float height; float g; };
    union { float z; float depth; float b; };
    union { float w; float time; float a; };

    Vector4() : x(0), y(0), z(0), w(0) {}
    ~Vector4() = default;
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
    Vector4& operator=(const Vector4& v)
    {
        x = v.x;
        y = v.y;
        z = v.z;
        w = v.w;
        return *this;
    }
}; //Vector4

} //Math
} //Steel
