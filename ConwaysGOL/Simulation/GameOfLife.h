// Simulation.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "HalTec\GameStates.h"
#include "HalTec\Vector2.h"
#include <vector>

class Cell;
class BoundingBox;

class GameOfLife : public GameState
{
private:
	//Use this vector to avoid changing cell states ahead of their neighbour checks.
	std::vector<std::pair<Vector2f, bool>> cellUpdates;

	Vector2f mMousePointerPosition;
	BoundingBox* mMousePointer = nullptr;
	Vector2f mGridOutlinePosition;
	BoundingBox* mGridOutline = nullptr;

	bool mIsPaused = true;
	Cell** mCells = nullptr;

	void EditCell(bool isAlive);

public:
	GameOfLife()  = default;
	~GameOfLife() = default;

	void Start() override;
	void End() override;

	void Update(double DeltaTime) override;
	void Render(SDL_Renderer& renderer) override;
};