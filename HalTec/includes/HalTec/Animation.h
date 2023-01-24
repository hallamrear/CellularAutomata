#pragma once
#include "Texture.h"
#include "Transform.h"

class AnimationController
{
	float mTimeBetweenFrames;
	float mTimeElapsed;
	float mDuration;
	unsigned int mCurrentFrame;
	Texture* mAnimationSheet;
	bool mIsLooping;
	unsigned int mCurrentAnimation;
	unsigned int mTotalFrames;

	//If the animation does not loop, this will set to true when it has finished playing.
	bool mHasFinished;

public:
	Vector2f FrameSize;

	AnimationController(std::string sheetPath, unsigned int numberOfAnimations, unsigned int frameCount, float duration, bool looping);
	~AnimationController();

	bool HasFinished();
	void Start();
	void SetAnimation(unsigned int animation);
	void Update(double deltaTime);
	void Render(SDL_Renderer& renderer, Transform transform);
	void Render(SDL_Renderer& renderer, Transform transform, bool flipped);
};

//class Animation
//{
//private:
//	float mTimeBetweenFrames;
//	float mTimeElapsed;
//	float mAnimationDuration;
//	bool mIsLooping;
//	unsigned int mCurrentFrame;
//	float FrameWidth;
//	float FrameHeight;
//
//public:
//	Animation(Vector2f FrameSize, float duration, bool looping)
//	{
//		mIsLooping = looping;
//		mAnimationDuration = duration;
//	};
//
//	~Animation()
//	{
//
//	};
//
//	inline void Update(double deltaTime)
//	{
//		mTimeElapsed += deltaTime;
//
//		if (mTimeElapsed > mAnimationDuration)
//		{
//			if (mIsLooping)
//			{
//				mTimeElapsed = 0.0f;
//				mCurrentFrame = 0;
//			}
//		}
//		else
//		{
//			mCurrentFrame = (unsigned int)(mTimeElapsed / mTimeBetweenFrames);
//		}
//	}
//
//	inline void Render(SDL_Renderer& renderer, Vector2f position, float rotation, Vector2f sourcePosition, Vector2f sourceDimensions)
//	{
//		Vector2f srcDim = Vector2f(FrameWidth, FrameHeight);
//		Vector2f srcPos = Vector2f((srcDim.X * mCurrentFrame) + (srcDim.X / 2.0f), FrameHeight / 2.0f);
//		Texture::Render(*Game::Renderer, position, rotation, srcPos, srcDim);
//	}
//};
