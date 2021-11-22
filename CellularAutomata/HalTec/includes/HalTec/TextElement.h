#pragma once
#include "Entity.h"
#include "Colour.h"

struct SDL_Texture;

class TextElement : public Entity
{
private:
	SDL_Texture*	mTextTexture;
	Transform		mTransform;
	bool			mIsDirty;
	bool			mIsShowing;
	std::string		mData;
	Colour			mColour;
	float			mFontSize;
	int				mTextWidth;
	int				mTextHeight;

	void DestroyTexture();
	void CreateTexture();

public:
	TextElement(
		Transform transform,
		std::string string = "", 
		float size = 14.0f, 
		Colour colour = Colour());
	~TextElement();

	void		Update(double deltaTime);
	void		Render();

	void		SetShowing(bool state);
	void		SetColour(Colour colour);
	void		SetString(std::string str);
	void		SetString(const char* str);
	void		SetPosition(Vector2f worldPosition);
	Vector2f	GetTextureSize();
};

