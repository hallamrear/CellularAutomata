// Simulation.cpp : Defines the entry point for the application.
#include "HalTec\OrientedBoundingBox.h"
#include "Simulation.h"
#include "Cell.h"
#include "HalTec\Settings.h"
#include "HalTec\InputManager.h"
#include "HalTec\Camera.h"
#include "HalTec\BoundingBox.h"

#include <iostream>
#include <cmath>

void Simulation::Start()
{
	mIsPaused = true;

	mMousePointer = new BoundingBox(mMousePointerPosition, CELL_SIZE, CELL_SIZE);
	mGridOutline = new BoundingBox(mGridOutlinePosition, CELL_SIZE * CELL_COUNT, CELL_SIZE * CELL_COUNT);

	InputManager::Bind(IM_KEY_CODE::IM_KEY_W, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.Y += 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_S, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.Y -= 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_A, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.X -= 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_D, IM_KEY_STATE::IM_KEY_HELD, [this]() { Vector2f pos = Camera::Get()->GetCameraPosition(); pos.X += 10.0f; Camera::Get()->SetCameraPosition(pos); });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_SPACE, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { mIsPaused = !mIsPaused; });
	InputManager::Bind(IM_KEY_CODE::IM_KEY_1, IM_KEY_STATE::IM_KEY_RELEASED, [this]() { mIsPaused = false; Update(0.0f); mIsPaused = true; });
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_LEFT_CLICK, IM_KEY_STATE::IM_KEY_RELEASED, std::bind(&Simulation::EditCell, this, true));
	InputManager::Bind(IM_MOUSE_CODE::IM_MOUSE_RIGHT_CLICK, IM_KEY_STATE::IM_KEY_RELEASED, std::bind(&Simulation::EditCell, this, false));

	srand(NULL);

	Settings::Get()->SetDrawColliders(true);

	Transform transform;

	mCells = new Cell*[CELL_COUNT];
	for (size_t x = 0; x < CELL_COUNT; x++)
	{
		mCells[x] = new Cell[CELL_COUNT];
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
			mCells[i][j].GetNeighbours(mCells);
		}
	}
}

void Simulation::End()
{
	if (mMousePointer)
	{
		delete mMousePointer;
		mMousePointer = nullptr;
	}
}

void Simulation::EditCell(bool isAlive)
{
	int gridX = (int)mMousePointerPosition.X / CELL_SIZE;
	int gridY = (int)mMousePointerPosition.Y / CELL_SIZE;

	if (gridX < 0 || gridY < 0 || gridX > CELL_COUNT || gridY > CELL_COUNT)
		return;
	else
		mCells[gridX][gridY].IsAlive = isAlive;
}

void Simulation::Update(double DeltaTime)
{
	mMousePointerPosition = InputManager::Get()->GetMouseWorldPosition(); 
	mMousePointerPosition.X = round(mMousePointerPosition.X / CELL_SIZE) * CELL_SIZE;
	mMousePointerPosition.Y = round(mMousePointerPosition.Y / CELL_SIZE) * CELL_SIZE;
	mMousePointer->Update(DeltaTime);

	mGridOutlinePosition = Vector2f((CELL_COUNT * CELL_SIZE) / 2.0f - (CELL_SIZE / 2.0f), (CELL_COUNT * CELL_SIZE) / 2.0f - (CELL_SIZE / 2.0f));
	mGridOutline->Update(DeltaTime);

	if (mIsPaused == false)
	{
		for (size_t j = 0; j < CELL_COUNT; j++)
		{
			for (size_t i = 0; i < CELL_COUNT; i++)
			{
				mCells[i][j].Update(DeltaTime);

				if (mCells[i][j].IsAlive)
				{
					//Underpopulation
					if (mCells[i][j].LivingNeighbourCount < 2)
						cellUpdates.push_back(std::make_pair(Vector2f(i, j), false));

					//Overpopulation
					if (mCells[i][j].LivingNeighbourCount > 3)
						cellUpdates.push_back(std::make_pair(Vector2f(i, j), false));
				}
				else
				{
					//Reproduction
					if (mCells[i][j].LivingNeighbourCount == 3)
						cellUpdates.push_back(std::make_pair(Vector2f(i, j), true));
				}
			}
		}

		int _x, _y;
		for (auto update : cellUpdates)
		{
			_x = (int)update.first.X;
			_y = (int)update.first.Y;
			mCells[_x][_y].IsAlive = update.second;
		}
		cellUpdates.clear();
	}

}

void Simulation::Render(SDL_Renderer& renderer)
{
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