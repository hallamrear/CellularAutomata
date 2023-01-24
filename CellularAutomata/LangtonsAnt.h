#pragma once
#include "HalTec\GameStates.h"
#include <HalTec\Vector2.h>
#include <random>
#include <cmath>

#define CELL_COUNT 100
#define CELL_SIZE 10.0f

enum AntDirection : int
{
	North = 1,
	South = 2,
	East = 3,
	West = 4
};

struct Ant
{
	int X;
	int Y;
	AntDirection Direction;

	Ant()
	{
		Direction = (AntDirection)(rand() % 4 + 1);

		X = round((rand() % CELL_COUNT) / CELL_SIZE) * CELL_SIZE;
		Y = round((rand() % CELL_COUNT) / CELL_SIZE) * CELL_SIZE;
	}

	void ChangeDirection(bool isClockwise)
	{
		if (isClockwise)
		{
			switch (Direction)
			{
			case North:
				Direction = East;
				break;
			case South:
				Direction = West;
				break;
			case East:
				Direction = South;
				break;
			case West:
				Direction = North;
				break;
			default:
				throw;
				break;
			}
		}
		else
		{
			switch (Direction)
			{
			case North:
				Direction = West;
				break;
			case South:
				Direction = East;
				break;
			case East:
				Direction = North;
				break;
			case West:
				Direction = South;
				break;
			default:
				throw;
				break;
			}
		}				
	}
};

class BoundingBox;
class OrientedBoundingBox;
class TextElement;
class Texture;

class LangtonsAnt : public GameState
{
public:
	LangtonsAnt()  = default;
	~LangtonsAnt() = default;

	void Start();
	void End();
	void Update(double DeltaTime);
	void Render(SDL_Renderer& renderer);

private:
	Ant mAnt;
	TextElement* mPausedText;
	bool mIsPaused = true;
	bool mCells[CELL_COUNT][CELL_COUNT];

	void FlipCell();

	//Rendering stuff
	Vector2f mGridOutlinePosition;
	BoundingBox* mGridOutline;
	Texture* mCellTexture;
	Texture* mAntTexture;
};