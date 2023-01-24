#pragma once
#include <string>
#include "Transform.h"

class Collider;
class Texture;
struct SDL_Renderer;

class Entity
{
private:

protected:
	SDL_Renderer&			mRenderer;
	Texture*				mTexture;
	Transform				mTransform;
	bool					mIsAlive;

	const SDL_Renderer&		GetRendererReference();
	void					ClampRotation();

public:
	std::string				Name;

	Entity(
		std::string texture_path = "",
		Transform transform = Transform());

	virtual					~Entity() = 0;

	//Sets mTexture to the texture at texture_path. Sets the width and height to the parameters.
	void					AssignTexture(const std::string& texture_path);
	const Texture&			GetTexture() const;

	virtual void			Update(double deltaTime) = 0;
	virtual void			Render() = 0;

	bool const				GetIsAlive()		 const { return mIsAlive; }
	Transform&				GetTransform()			   { return mTransform; }
	
	virtual void			SetAlive(const bool state) { mIsAlive = state; }
};