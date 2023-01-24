#pragma once
#include <map>
#include "GameStates.h"

enum class GameStateIdentifier
{	
	GAME_STATE_UNKNOWN = 0,
	GAME_STATE_PAUSED,
	GAME_STATE_PLAYING,
	GAME_STATE_MAIN_MENU,
	GAME_STATE_1,
	GAME_STATE_2,
	GAME_STATE_3,
	GAME_STATE_4,
	GAME_STATE_5,
	GAME_STATE_6,
	GAME_STATE_7,
	GAME_STATE_8,
	GAME_STATE_9
};

class StateDirector
{
private:
	static StateDirector* mInstance;

	GameState* mCurrentState;
	std::map<GameStateIdentifier, GameState*> mDirectorStates;

							StateDirector();
							~StateDirector();

	void					SetState_Impl(const GameStateIdentifier state);
	void					SetupState_Impl(GameStateIdentifier identifier, GameState* state);
	const GameState*		GetState_Impl();
	static StateDirector*	Get();
	void					Update_Impl(double DeltaTime);
	void					Render_Impl(SDL_Renderer& renderer);

public:
	static void				SetState(const GameStateIdentifier state);
	static void				SetupState(GameStateIdentifier identifier, GameState* state);
	static const GameState*	GetState();
	static void				Update(double DeltaTime);
	static void				Render(SDL_Renderer& renderer);
};
