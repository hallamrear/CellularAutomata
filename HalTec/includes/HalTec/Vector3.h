#pragma once

class Vector3f
{
public:
	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;

	Vector3f(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		this->X = X;
		this->Y = Y;
		this->Z = Z;
	}

	~Vector3f()
	{
		X = 0.0f;
		Y = 0.0f;
		Z = 0.0f;
	}

};



