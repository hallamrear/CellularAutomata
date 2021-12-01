#pragma once
#include "HalTec/Entity.h"
#include <vector>

#define CELL_COUNT 100
#define CELL_SIZE 10.0f

class OrientedBoundingBox;
class BoundingBox;

class Cell : public Entity
{
public:
	Cell();
	~Cell();

	void GetNeighbours(Cell** grid);

	void Update(double DeltaTime);
	void Render() {};
	void Render(SDL_Renderer& renderer);

	int LivingNeighbourCount;
	bool IsAlive;
private:

	int mNeighbourCount;
	std::vector<Cell*> mNeighbours;
};
