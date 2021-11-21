#pragma once
#include "Collision.h"

class BoundingSphere
	: public Collider
{
public:
	float Radius = 0;

	BoundingSphere(Vector2f& position, float radius);
	virtual ~BoundingSphere();

	virtual void Update(double deltaTime);
	virtual void Render(SDL_Renderer& renderer);

	virtual Vector2f FindFurthestPoint(Vector2f direction) const override;
	virtual void GetColliderAsPoints(Vector2f points[]) const override;
};