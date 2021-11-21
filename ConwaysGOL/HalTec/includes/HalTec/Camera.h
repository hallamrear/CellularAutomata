#pragma once
#include "Vector2.h"

class Camera
{
private:
	static Camera* mInstance;
	Vector2f mPosition;

	Camera();
	void SetCameraPosition_Impl(Vector2f position);
	Vector2f GetCameraPosition_Impl();
	Vector2f WorldToScreen_Impl(Vector2f entityWorldPosition);


	Vector2f ScreenToWorld_Impl(Vector2f screenPosition);

public:
	~Camera();
	static Camera* Get();

	static void SetCameraPosition(Vector2f position);
	static Vector2f GetCameraPosition();
	static Vector2f WorldToScreen(Vector2f entityWorldPosition);
	static Vector2f ScreenToWorld(Vector2f screenPosition);
};

//todo : figure out a zoom thing with SDL_RenderSetScale();