#include "LangtonsAnt.h"
#include "HalTec\BoundingBox.h"
#include "HalTec\Settings.h"
#include "HalTec\InputManager.h"
#include "HalTec\Camera.h"
#include "HalTec\OrientedBoundingBox.h"
#include "HalTec/TextElement.h"

#include <iostream>

void LangtonsAnt::Start()
{
	srand(NULL);
	Settings::Get()->SetDrawColliders(true);

	InputManager::Bind(IM_KEY_CODE::IM_KEY_W, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.Y += 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_S, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.Y -= 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_A, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.X -= 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_D, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.X += 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_SPACE, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { mIsPaused = !mIsPaused; });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_1, IM_KEY_STATE::IM_KEY_RELEASED, [this]() { mIsPaused = false; Update(0.0f); mIsPaused = true; });
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_LEFT_CLICK, IM_KEY_STATE::IM_KEY_RELEASED, std::bind(&LangtonsAnt::FlipCell, this));
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_MIDDLE_CLICK, IM_KEY_STATE::IM_KEY_RELEASED,
		[this]() 
		{
			mAnt.X = round((int)InputManager::Get()->GetMouseWorldPosition().X / CELL_SIZE);
			mAnt.Y = round((int)InputManager::Get()->GetMouseWorldPosition().Y / CELL_SIZE);			
		} );

	mPausedText = new TextElement(Transform());
	mGridOutline = new BoundingBox(mGridOutlinePosition, CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT);
	mGridOutlinePosition = Vector2f((CELL_COUNT * CELL_SIZE) / 2.0f - (CELL_SIZE / 2.0f), (CELL_COUNT * CELL_SIZE) / 2.0f - (CELL_SIZE / 2.0f));
	mGridOutline->Update(0.0);

	mAntOutline = new BoundingBox(mAntOutlinePosition, CELL_SIZE, CELL_SIZE);

	mCellOutlines = new OrientedBoundingBox** [CELL_COUNT];
	for (int C = 0; C < CELL_COUNT; C++)
		mCellOutlines[C] = new OrientedBoundingBox*[CELL_COUNT];

	for (int j = 0; j < CELL_COUNT; j++)
	{
		for (int i = 0; i < CELL_COUNT; i++)
		{
			mCells[i][j] = false;
			float rotation = 0.0f;
			mCellOutlinePositions[i][j].X = i * CELL_SIZE;
			mCellOutlinePositions[i][j].Y = j * CELL_SIZE;
			mCellOutlines[i][j] = new OrientedBoundingBox(mCellOutlinePositions[i][j], rotation, CELL_SIZE, CELL_SIZE);
		}
	}
}

void LangtonsAnt::End()
{
	if (mPausedText)
	{
		delete mPausedText;
		mPausedText = nullptr;
	}

	if (mGridOutline)
	{
		delete mGridOutline;
		mGridOutline = nullptr;
	}

	if (mAntOutline)
	{
		delete mAntOutline;
		mAntOutline = nullptr;
	}

	for (int i = 0; i < CELL_COUNT; i++)
	{
		for (int j = 0; j < CELL_COUNT; j++)
		{
			delete[] mCellOutlines[i][j];
			mCellOutlines[i][j] = nullptr;
		}

		delete[] mCellOutlines[i];
		mCellOutlines[i] = nullptr;
	}
	delete[] mCellOutlines;
	mCellOutlines = nullptr;
}

void LangtonsAnt::FlipCell()
{
	int gridX = round((int)InputManager::Get()->GetMouseWorldPosition().X / CELL_SIZE);
	int gridY = round((int)InputManager::Get()->GetMouseWorldPosition().Y / CELL_SIZE);

	if (gridX < 0 || gridY < 0 || gridX > CELL_COUNT || gridY > CELL_COUNT)
		return;
	else
		mCells[gridX][gridY] = !mCells[gridX][gridY];
}

void LangtonsAnt::Update(double DeltaTime)
{
	mPausedText->Update(DeltaTime);

	if (mIsPaused)
	{
		mPausedText->SetString("Paused!");
		mPausedText->SetPosition(Camera::ScreenToWorld(Settings::Get()->GetWindowCentre()));
	}
	else
	{
		mPausedText->SetString("!");
		mPausedText->SetPosition(Vector2f(-5000.0f, -5000.0f));

		mAntOutlinePosition = Vector2f(mAnt.X * CELL_SIZE, mAnt.Y * CELL_SIZE);
		mAntOutline->Update(DeltaTime);

		if (mCells[mAnt.X][mAnt.Y] == true)
			//turn clockwise 90
			mAnt.ChangeDirection(true);
		else
			//turn anti-clockwise 90
			mAnt.ChangeDirection(false);

		//flip cell
		mCells[mAnt.X][mAnt.Y] = !mCells[mAnt.X][mAnt.Y];

		//move forward
		switch (mAnt.Direction)
		{
		case North:
			mAnt.Y++;
			break;
		case South:
			mAnt.Y--;
			break;
		case East:
			mAnt.X++;
			break;
		case West:
			mAnt.X--;
			break;

		default:
			break;
		}

		//Wraparound
		if (mAnt.X < 0)
			mAnt.X += CELL_COUNT;
		if (mAnt.Y < 0)
			mAnt.Y += CELL_COUNT;
		if (mAnt.X > CELL_COUNT)
			mAnt.X -= CELL_COUNT;
		if (mAnt.Y > CELL_COUNT)
			mAnt.Y -= CELL_COUNT;
	}
}

void LangtonsAnt::Render(SDL_Renderer& renderer)
{
	if (mIsPaused)
		mPausedText->Render();

	for (size_t j = 0; j < CELL_COUNT; j++)
	{
		for (size_t i = 0; i < CELL_COUNT; i++)
		{
			if (mCells[i][j])
			{
				mCellOutlines[i][j]->Render(renderer);
			}
		}
	}

	if (mGridOutline)
		mGridOutline->Render(renderer);

	if (mAntOutline)
		mAntOutline->Render(renderer);

}