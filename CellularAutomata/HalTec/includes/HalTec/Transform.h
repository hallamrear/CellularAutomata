#pragma once
#include "Helper.h"

struct Transform
{
	Vector2f Position;
	float Rotation;

	Transform(Vector2f position = Vector2f(), float rotation = 0.0f)
	{
		this->Position = position;
		this->Rotation = rotation;
	}

	void Reset()
	{
		Position = Vector2f(0.0f, 0.0f);
		Rotation = 0.0f;
	}

	Vector2f GetUp() const
	{
		return Vector2f(RotatePointAroundOriginDegrees(Vector2f(0.0f, 1.0f), 360.0f - Rotation, Vector2f())).GetNormalized();
	}

	Vector2f GetDown() const
	{
		return Vector2f(RotatePointAroundOriginDegrees(Vector2f(0.0f, -1.0f), 360.0f - Rotation, Vector2f()).GetNormalized());
	}

	Vector2f GetRight() const
	{
		return Vector2f(RotatePointAroundOriginDegrees(Vector2f(1.0f, 0.0f), 360.0f - Rotation, Vector2f()).GetNormalized());
	}

	Vector2f GetLeft() const
	{
		return Vector2f(RotatePointAroundOriginDegrees(Vector2f(-1.0f, 0.0f), 360.0f - Rotation, Vector2f()).GetNormalized());
	}
	
	void AdjustPosition(const Vector2f offset)
	{
		Position += offset;
	}

	void AdjustRotation(const float angle)
	{
		Rotation += angle;
	}
};

