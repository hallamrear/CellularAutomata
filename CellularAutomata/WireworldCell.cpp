#include "WireworldCell.h"
#include <HalTec\TextureCache.h>
#include <HalTec\Texture.h>

const Vector2f cellOffsets[8] =
{
	/* NW */ Vector2f(-1.0f, 1.0f),
	/* N  */ Vector2f(0.0f, 1.0f),
	/* NE */ Vector2f(1.0f, 1.0f),
	/* E  */ Vector2f(1.0f, 0.0f),
	/* SE */ Vector2f(1.0f,-1.0f),
	/* S  */ Vector2f(0.0f,-1.0f),
	/* SW */ Vector2f(-1.0f,-1.0f),
	/* W  */ Vector2f(-1.0f, 0.0f)
};

WireworldCell::WireworldCell() : Entity()
{
	State = WireworldState::Empty;
	mElectronHeadTexture = TextureCache::GetTexture("Assets/ElectronHead.bmp");
	mElectronTailTexture = TextureCache::GetTexture("Assets/ElectronTail.bmp");
	mConductorTexture = TextureCache::GetTexture("Assets/Conductor.bmp");
}

WireworldCell::~WireworldCell()
{

}

void WireworldCell::FillNeighbours(WireworldCell** grid)
{
	Neighbours.clear();
	NeighbourCount = 0;

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
			Neighbours.push_back(&grid[neighbourPosX][neighbourPosY]);
	}

	NeighbourCount = Neighbours.size();
}

void WireworldCell::Update(double DeltaTime)
{
	ElectronHeadsNearby = 0;

	for (size_t n = 0; n < NeighbourCount; n++)
	{
		if (Neighbours[n]->State == WireworldState::Electron_Head)
			ElectronHeadsNearby++;
	}
}

void WireworldCell::Render(SDL_Renderer& renderer)
{
	if (State == WireworldState::Empty)
		return;

	switch (State)
	{
	case WireworldState::Electron_Head:
		mElectronHeadTexture->Render(renderer, mTransform.Position, 0.0f);
		break;
	case WireworldState::Electron_Tail:
		mElectronTailTexture->Render(renderer, mTransform.Position, 0.0f);
		break;
	case WireworldState::Conductor:
		mConductorTexture->Render(renderer, mTransform.Position, 0.0f);
		break;
	default:
	case WireworldState::Empty:
		break;
	}
}