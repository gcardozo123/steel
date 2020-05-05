#include "./transform.hpp"

namespace Steel
{
	void Transform::_SetSize(double width, double height)
	{
		scale.x = width / original_size.width;
		scale.y = height / original_size.height;

		size.width = width;
		size.height = height;
	}

	void Transform::_SetPosition(double x, double y)
	{
		position.x = x;
		position.y = y;
	}

	void Transform::_SetScale(double x, double y)
	{
		scale.x = x;
		scale.y = y;

		size.x = original_size.x * scale.x;
		size.y = original_size.y * scale.y;
	}
	
	void Transform::SetScale(double value)
	{
		_SetScale(value, value);
	}
	
	void Transform::SetScale(const Vector2 &value)
	{
		_SetScale(value.x, value.y);
	}
	
	void Transform::SetScale(double x, double y)
	{
		_SetScale(x, y);
	}
	
	void Transform::SetPosition(const Vector2 &value)
	{
		_SetPosition(value.x, value.y);
	}
	
	void Transform::SetPosition(double x, double y)
	{
		_SetPosition(x, y);
	}
	
	void Transform::SetSize(double width, double height)
	{
		_SetSize(width, height);
	}
	
	void Transform::SetSize(const Vector2 &value)
	{
		_SetSize(value.width, value.height);
	}
	
	void Transform::SetOriginalSize(const Vector2 & value)
	{
		original_size.x = value.x;
		original_size.y = value.y;

		_SetScale(1.0, 1.0);
	}
}