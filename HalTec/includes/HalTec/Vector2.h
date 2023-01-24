#pragma once
#include <math.h>

class Vector2f
{
public:
	float X;
	float Y;

	Vector2f();
	Vector2f(float x, float y);
	
	float GetAngleDegrees() const;
	float GetAngleRadians() const;
	float GetMagnitude() const;
	float GetMagnitudeSquared() const;
	Vector2f GetNormalized() const;
	Vector2f GetVectorRotatedByAngle(float angleDegrees);
	float Dot(Vector2f vector) const;

	//Operators
	Vector2f& operator= (const Vector2f& other);
	Vector2f operator+(const Vector2f& rhs);
	Vector2f operator-(const Vector2f& rhs);
	Vector2f operator*(const float& scalar);
	Vector2f operator/(const float& scalar);
	Vector2f& operator+=(const Vector2f& rhs);
	Vector2f& operator-=(const Vector2f& rhs);
	bool operator!=(const Vector2f& rhs);
	bool operator==(const Vector2f& rhs);
	friend bool operator==(const Vector2f& lhs, const Vector2f& rhs);
	friend Vector2f operator-(const Vector2f& lhs, const Vector2f& rhs);
};