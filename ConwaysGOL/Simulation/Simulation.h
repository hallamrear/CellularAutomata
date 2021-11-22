// Simulation.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "HalTec\GameStates.h"
#include "HalTec\Vector2.h"
#include <vector>

class Cell;
class BoundingBox;

class Simulation : public GameState
{
private:
	//Use this vector to avoid changing cell states ahead of their neighbour checks.
	std::vector<std::pair<Vector2f, bool>> cellUpdates;

	Vector2f mMousePointerPosition;
	BoundingBox* mMousePointer;
	Vector2f mGridOutlinePosition;
	BoundingBox* mGridOutline;

	bool mIsPaused;
	Cell** mCells;

	void EditCell(bool isAlive);

public:
	Simulation()  = default;
	~Simulation() = default;

	void Start() override;
	void End() override;

	void Update(double DeltaTime) override;
	void Render(SDL_Renderer& renderer) override;
};