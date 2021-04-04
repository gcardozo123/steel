#pragma once

#include <iostream>

#include "core.hpp"
#include "steel_math.hpp"

namespace Steel
{
namespace Math
{
    class Vector2
	{
	public:
		union { float x; float width; };
		union { float y; float height; };
		
		Vector2() : x(0.0), y(0.0){}
		~Vector2() = default;
		Vector2(float x, float y) : x(x), y(y){}
		Vector2(const Vector2& v) : x(v.x), y(v.y) {}
        Vector2& operator=(const Vector2& v)
        {
            x = v.x;
            y = v.y;
            return *this;
        }

        friend std::ostream& operator<<(std::ostream& os, Vector2 v)
        {
            os << "(" << v.x << ", " << v.y << ")";
            return os;
        }

		Vector2 Copy() const
        {
            return Vector2(x, y);
        }

        static Vector2 Up()
        {
            return Vector2(0.0, 1.0);
        }

        static Vector2 Down()
        {
            return Vector2(0.0, -1.0);
        }

        static Vector2 Left()
        {
            return Vector2(-1.0, 0.0);
        }

        static Vector2 Right()
        {
            return Vector2(1.0, 0.0);
        }

        static Vector2 Zero()
        {
            return Vector2();
        }

        static Vector2 Unity()
        {
            return Vector2(1.0, 1.0);
        }

        bool operator==(const Vector2& v) const
        {
		    return x == v.x && y == v.y;
        }

        Vector2 operator+(const Vector2& v) const
		{
			return Vector2(x + v.x, y + v.y);
		}

		Vector2& operator+=(const Vector2& v)
		{
			x += v.x;
			y += v.y;
			return *this;
		}

        Vector2 operator-(const Vector2& v) const
        {
            return Vector2(x - v.x, y - v.y);
        }

        Vector2 operator-() const
        {
            return Vector2(-x, -y);
        }

		Vector2& operator-=(const Vector2& v)
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vector2 operator*(float v) const
		{
            return Vector2(x * v, y * v);
		}

        Vector2& operator*=(float v)
        {
            x *= v;
            y *= v;
            return *this;
        }
		
		Vector2 operator/(float v) const
		{
            return Vector2(x / v, y / v);
		}
		
		Vector2& operator/=(float v)
		{
			x /= v;
			y /= v;
			return *this;
		}

		void Set(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		Vector2 Rotated(float deg) const
		{
		    float theta = ( deg / 180.0f ) * Math::Pi;
			float c = cos(theta);
			float s = sin(theta);
			float tx = x * c - y * s;
			float ty = x * s + y * c;
			return Vector2(tx, ty);
		}

		void Rotate(float deg)
        {
		    *this = Rotated(deg);
        }

		Vector2 Normalized() const
        {
            Vector2 res = this->Copy();
		    if (Length() == 0)
            {
                return res;
            }
            return res * (1.0f / Length());
        }

        void Normalize()
		{
			*this = Normalized();
		}

		static float Distance(const Vector2& a, const Vector2& b)
		{
            float v1 = a.x - b.x, v2 = a.y - b.y;
            return Math::Sqrt(v1 * v1 + v2 * v2);
		}

        static float DistanceSquared(Vector2 a, Vector2 b)
        {
            float v1 = a.x - b.x, v2 = a.y - b.y;
            return (v1 * v1) + (v2 * v2);
        }

		float Length() const
		{
			return Math::Sqrt(x * x + y * y);
		}

        float LengthSquared() const
        {
            return (x * x) + (y * y);
        }

        /// Divides the components of a "Vector2" by the components of another "Vector2".
		static Vector2 Divide(Vector2 a, Vector2 b)
        {
            a.x /= b.x;
            a.y /= b.y;
            return a;
        }

        static float Dot(Vector2 v1, Vector2 v2)
        {
            return v1.x * v2.x + v1.y * v2.y;
        }

        // Computes the z-component of 2 vectors lying on the xy-plane:
        static float Cross(Vector2 v1, Vector2 v2)
        {
            return (v1.x * v2.y) - (v1.y * v2.x);
        }

        Vector2 Floor() const
        {
		    return Vector2(Math::Floor(x), Math::Floor(y));
        }

        Vector2 Ceiling() const
        {
            return Vector2(Math::Ceiling(x), Math::Ceiling(y));
        }

		void Truncate(float length)
		{
			float angle = atan2f(y, x);
			x = length * cos(angle);
			y = length * sin(angle);
		}

        // Returns a "Vector2" that is perpendicular towards the clockwise direction
		Vector2 PerpendicularClockwise() const
        {
            return Vector2(y, -x);
        }

        // Returns a "Vector2" that is perpendicular towards the counter-clockwise direction
        Vector2 PerpendicularCounterClockwise() const
        {
            return Vector2(-y, x);
        }

	}; //Vector2
} //Math
} //Steel