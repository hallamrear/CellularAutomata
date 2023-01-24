#pragma once

struct SDL_Renderer;

class GameState
{
public:
	virtual ~GameState() = default;
	virtual void Start() = 0;
	virtual void Update(double) = 0;
	virtual void Render(SDL_Renderer&) = 0;
	virtual void End() = 0;
};