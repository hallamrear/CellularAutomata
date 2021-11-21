// Simulation.h : Include file for standard system include files,
// or project specific include files.

#pragma once
#include "HalTec\GameStates.h"

class Simulation : public GameState
{
	Simulation()  = default;
	~Simulation() = default;

	void Start() override;
	void End() override;

	void Update(double DeltaTime) override;
	void Render(SDL_Renderer& renderer) override;
};

// TODO: Reference additional headers your program requires here.
