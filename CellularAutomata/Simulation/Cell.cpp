#include "Cell.h"
#include "HalTec\OrientedBoundingBox.h"
#include <random>

const Vector2f cellOffsets[8] =
{
	/* NW */ Vector2f(-1.0f, 1.0f),
	/* N  */ Vector2f( 0.0f, 1.0f),
	/* NE */ Vector2f( 1.0f, 1.0f),
	/* E  */ Vector2f( 1.0f, 0.0f),
	/* SE */ Vector2f( 1.0f,-1.0f),
	/* S  */ Vector2f( 0.0f,-1.0f),
	/* SW */ Vector2f(-1.0f,-1.0f),
	/* W  */ Vector2f(-1.0f, 0.0f)
};

Cell::Cell()
	: Entity("", Transform())
{
	IsAlive = false;
	mDeadBox = new OrientedBoundingBox(mTransform.Position, mTransform.Rotation, CELL_SIZE, CELL_SIZE);
	mAliveBox = new BoundingBox(mTransform.Position, CELL_SIZE, CELL_SIZE);
}

Cell::~Cell()
{
	mNeighbours.clear();
	mNeighbourCount = 0;

	if (mDeadBox)
	{
		delete mDeadBox;
		mDeadBox = nullptr;
	}
}

void Cell::GetNeighbours(Cell** grid)
{
	mNeighbours.clear();
	mNeighbourCount = 0;

	int gridPosX = static_cast<int>(mTransform.Position.X / CELL_SIZE);
	int gridPosY = static_cast<int>(mTransform.Position.Y / CELL_SIZE);

	int neighbourPosX, neighbourPosY;

	for (int i = 0; i < 8; i++)
	{
		neighbourPosX = gridPosX + (int)cellOffsets[i].X;
		neighbourPosY = gridPosY + (int)cellOffsets[i].Y;

		if (neighbourPosX < 0 || neighbourPosY < 0 || neighbourPosX >= CELL_COUNT || neighbourPosY >= CELL_COUNT)
			continue;
		else
			mNeighbours.push_back(&grid[neighbourPosX][neighbourPosY]);
	}

	mNeighbourCount = mNeighbours.size();
}

void Cell::Update(double DeltaTime)
{
	mDeadBox->Update(DeltaTime);
	mAliveBox->Update(DeltaTime);

	int aliveCount = 0;
	for (size_t i = 0; i < mNeighbourCount; i++)
	{
		if (mNeighbours[i]->IsAlive)
			aliveCount++;
	}	

	LivingNeighbourCount = aliveCount;
}

void Cell::Render(SDL_Renderer& renderer)
{
	if (IsAlive)
		mAliveBox->Render(renderer);
}