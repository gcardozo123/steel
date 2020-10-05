#pragma once

#include <cmath>

#include "core.hpp"

namespace Steel
{
	class Vector2
	{
	private:
	
	public:
		union { double x; double width; };
		union { double y; double height; };
		
		Vector2() : x(0.0), y(0.0){}
		Vector2(double x, double y) : x(x), y(y){}
		Vector2(const Vector2& v) : x(v.x), y(v.y) {}

		Vector2 Copy();
		Vector2 Up();
		Vector2 Down();
		Vector2 Left();
		Vector2 Right();
		Vector2 Zero();

		Vector2 operator+(Vector2& v) 
		{
			return Vector2(x + v.x, y + v.y);
		}
		
		Vector2 operator-(Vector2& v) 
		{
			return Vector2(x - v.x, y - v.y);
		}

		Vector2& operator+=(Vector2& v) 
		{
			x += v.x;
			y += v.y;
			return *this;
		}

		Vector2& operator-=(Vector2& v) 
		{
			x -= v.x;
			y -= v.y;
			return *this;
		}

		Vector2 operator+(double s) 
		{
			return Vector2(x + s, y + s);
		}

		Vector2 operator-(double s) 
		{
			return Vector2(x - s, y - s);
		}

		Vector2 operator*(double s) 
		{
			return Vector2(x * s, y * s);
		}
		
		Vector2 operator/(double s) 
		{
			return Vector2(x / s, y / s);
		}

		Vector2& operator+=(double s) 
		{
			x += s;
			y += s;
			return *this;
		}
		Vector2& operator-=(double s) 
		{
			x -= s;
			y -= s;
			return *this;
		}
		
		Vector2& operator*=(double s) 
		{
			x *= s;
			y *= s;
			return *this;
		}
		
		Vector2& operator/=(double s) 
		{
			x /= s;
			y /= s;
			return *this;
		}

		void Set(double x, double y) 
		{
			this->x = x;
			this->y = y;
		}

		void Rotate(double deg) 
		{
			double theta = deg / 180.0 * PI;
			double c = cos(theta);
			double s = sin(theta);
			double tx = x * c - y * s;
			double ty = x * s + y * c;
			x = tx;
			y = ty;
		}

		Vector2& Normalize() 
		{
			//TODO review this:
			if (Length() == 0) 
				return *this;
			
			*this *= (1.0 / Length());
			return *this;
		}

		float Dist(Vector2 v) const 
		{
			Vector2 d(v.x - x, v.y - y);
			return d.Length();
		}

		float Length() const 
		{
			return std::sqrt(x * x + y * y);
		}
		
		void Truncate(double length) 
		{
			double angle = atan2f(y, x);
			x = length * cos(angle);
			y = length * sin(angle);
		}

		Vector2 Ortho() const {
			return Vector2(y, -x);
		}

		static float Dot(Vector2 v1, Vector2 v2) 
		{
			return v1.x * v2.x + v1.y * v2.y;
		}
		
		static float Cross(Vector2 v1, Vector2 v2) 
		{
			return (v1.x * v2.y) - (v1.y * v2.x);
		}
	};
}