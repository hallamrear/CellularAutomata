#pragma once
#include "BoundingBox.h"

class OrientedBoundingBox : public BoundingBox
{
protected:
	void CalculateRotations();

public:
	float& Rotation;
	Vector2f TopRight;
	Vector2f BottomLeft;

	OrientedBoundingBox(Vector2f& position, float& rotation, float size_x, float size_y);
	~OrientedBoundingBox();

	virtual void Update(double deltaTime);
	virtual void Render(SDL_Renderer& renderer);

	//Fills array with points of the box.
	void GetColliderAsPoints(Vector2f points[]) const;
};
