#pragma once
#include <HalTec/Entity.h>

#define CELL_COUNT 100
#define CELL_SIZE 10.0f

enum class WireworldState : int
{
	Empty = 0,
	Electron_Head = 1,
	Electron_Tail = 2,
	Conductor = 3
};

class WireworldCell : public Entity
{
private:
	Texture* mElectronHeadTexture;
	Texture* mElectronTailTexture;
	Texture* mConductorTexture;

public:
	WireworldCell();
	~WireworldCell();

	void Update(double DeltaTime);
	void Render() {};
	void Render(SDL_Renderer& renderer);

	void FillNeighbours(WireworldCell** grid);

	WireworldState State;
	int NeighbourCount;
	std::vector<WireworldCell*> Neighbours;
	int ElectronHeadsNearby;
};