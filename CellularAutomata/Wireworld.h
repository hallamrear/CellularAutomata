#pragma once
#include "HalTec\GameStates.h"
#include "HalTec\Vector2.h"
#include <vector>

enum class WireworldState;
class WireworldCell;
class BoundingBox;
class TextElement;

class Wireworld : public GameState
{
private:
	//Use this vector to avoid changing cell states ahead of their neighbour checks.
	std::vector<std::pair<Vector2f, WireworldState>> cellUpdates;

	Vector2f mMousePointerPosition;
	BoundingBox* mMousePointer = nullptr;
	Vector2f mGridOutlinePosition;
	BoundingBox* mGridOutline = nullptr;

	TextElement* mPausedText;
	bool mIsPaused = true;
	WireworldCell** mCells = nullptr;

	void EditCell(WireworldState state);

public:
	Wireworld() = default;
	~Wireworld() = default;

	void Start() override;
	void End() override;

	void Update(double DeltaTime) override;
	void Render(SDL_Renderer& renderer) override;
};