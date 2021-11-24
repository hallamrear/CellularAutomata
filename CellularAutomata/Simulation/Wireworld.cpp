#include "Wireworld.h"
#include <HalTec\InputManager.h>
#include "HalTec\OrientedBoundingBox.h"
#include "GameOfLife.h"
#include "WireworldCell.h"
#include "HalTec\Settings.h"
#include "HalTec\InputManager.h"
#include "HalTec\Camera.h"
#include "HalTec\BoundingBox.h"
#include "HalTec/TextElement.h"

#include <iostream>

void Wireworld::EditCell(WireworldState state)
{
	int gridX = (int)mMousePointerPosition.X / CELL_SIZE;
	int gridY = (int)mMousePointerPosition.Y / CELL_SIZE;

	if (gridX < 0 || gridY < 0 || gridX > CELL_COUNT || gridY > CELL_COUNT)
		return;
	else
		mCells[gridX][gridY].State = state;
}

void Wireworld::Start()
{
	mIsPaused = true;
	mPausedText = new TextElement(Transform());

	mMousePointer = new BoundingBox(mMousePointerPosition, CELL_SIZE, CELL_SIZE);
	mGridOutline = new BoundingBox(mGridOutlinePosition, CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT);

	InputManager::Bind(IM_KEY_CODE::IM_KEY_W, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.Y += 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_S, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.Y -= 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_A, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.X -= 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_D, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.X += 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_SPACE, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { mIsPaused = !mIsPaused; });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_1, IM_KEY_STATE::IM_KEY_RELEASED, [this]() { mIsPaused = false; Update(0.0f); mIsPaused = true; });
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_LEFT_CLICK, IM_KEY_STATE::IM_KEY_HELD, std::bind(&Wireworld::EditCell, this, WireworldState::Conductor));
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_MIDDLE_CLICK, IM_KEY_STATE::IM_KEY_HELD, std::bind(&Wireworld::EditCell, this, WireworldState::Empty));
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_RIGHT_CLICK, IM_KEY_STATE::IM_KEY_HELD, std::bind(&Wireworld::EditCell, this, WireworldState::Electron_Head));

	srand(NULL);

	Settings::Get()->SetDrawColliders(true);

	Transform transform;

	mCells = new WireworldCell*[CELL_COUNT];
	for (size_t x = 0; x < CELL_COUNT; x++)
	{
		mCells[x] = new WireworldCell[CELL_COUNT];
	}

	for (size_t j = 0; j < CELL_COUNT; j++)
	{
		for (size_t i = 0; i < CELL_COUNT; i++)
		{
			mCells[i][j].GetTransform().Position.X = (float)i * CELL_SIZE;
			mCells[i][j].GetTransform().Position.Y = (float)j * CELL_SIZE;
		}
	}

	for (size_t j = 0; j < CELL_COUNT; j++)
	{
		for (size_t i = 0; i < CELL_COUNT; i++)
		{
			mCells[i][j].FillNeighbours(mCells);
		}
	}
}

void Wireworld::End()
{
	if (mPausedText)
	{
		delete mPausedText;
		mPausedText = nullptr;
	}

	if (mMousePointer)
	{
		delete mMousePointer;
		mMousePointer = nullptr;
	}

	if (mGridOutline)
	{
		delete mGridOutline;
		mGridOutline = nullptr;
	}

	for (size_t j = 0; j < CELL_COUNT; j++)
	{
		delete[] mCells[j];
		mCells[j] = nullptr;
	}

	delete[] mCells;
	mCells = nullptr;

}

void Wireworld::Update(double DeltaTime)
{
	_sleep(20);

	mMousePointerPosition = InputManager::Get()->GetMouseWorldPosition();
	mMousePointerPosition.X = round(mMousePointerPosition.X / CELL_SIZE) * CELL_SIZE;
	mMousePointerPosition.Y = round(mMousePointerPosition.Y / CELL_SIZE) * CELL_SIZE;
	mMousePointer->Update(DeltaTime);

	mGridOutlinePosition = Vector2f((CELL_COUNT * CELL_SIZE) / 2.0f - (CELL_SIZE / 2.0f), (CELL_COUNT * CELL_SIZE) / 2.0f - (CELL_SIZE / 2.0f));
	mGridOutline->Update(DeltaTime);
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

		for (size_t j = 0; j < CELL_COUNT; j++)
		{
			for (size_t i = 0; i < CELL_COUNT; i++)
			{
				mCells[i][j].Update(DeltaTime);
				
				switch (mCells[i][j].State)
				{
				default:
				case WireworldState::Empty:
					break;
				case WireworldState::Electron_Head:
					cellUpdates.push_back(std::make_pair(Vector2f(i, j), WireworldState::Electron_Tail));
					break;
				case WireworldState::Electron_Tail:
					cellUpdates.push_back(std::make_pair(Vector2f(i, j), WireworldState::Conductor));
					break;
				case WireworldState::Conductor:

					if (mCells[i][j].ElectronHeadsNearby == 1 || mCells[i][j].ElectronHeadsNearby == 2)
					{
						cellUpdates.push_back(std::make_pair(Vector2f(i, j), WireworldState::Electron_Head));
					}
					break;
				}
				
			}
		}

		int _x, _y;
		for (auto update : cellUpdates)
		{
			_x = (int)update.first.X;
			_y = (int)update.first.Y;
			mCells[_x][_y].State = update.second;
		}
		cellUpdates.clear();
	}
}

void Wireworld::Render(SDL_Renderer& renderer)
{
	if (mIsPaused)
		mPausedText->Render();

	for (size_t j = 0; j < CELL_COUNT; j++)
	{
		for (size_t i = 0; i < CELL_COUNT; i++)
		{
			mCells[i][j].Render(renderer);
		}
	}

	mGridOutline->Render(renderer);
	mMousePointer->Render(renderer);
}