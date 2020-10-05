#include "./vector2.hpp"

namespace Steel
{
	Vector2 Vector2::Copy()
	{
		return Vector2(x, y);
	}
	Vector2 Vector2::Up()
	{
		return Vector2(0.0, 1.0);
	}
	Vector2 Vector2::Down()
	{
		return Vector2(0.0, -1.0);
	}
	Vector2 Vector2::Left()
	{
		return Vector2(-1.0, 0.0);
	}
	Vector2 Vector2::Right()
	{
		return Vector2(1.0, 0.0);
	}
	Vector2 Vector2::Zero()
	{
		return Vector2();
	}
}