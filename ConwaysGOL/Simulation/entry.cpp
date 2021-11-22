#include "GameOfLife.h"
#include "LangtonsAnt.h"
#include "HalTec\Game.h"
#include "HalTec\StateDirector.h"
#include "HalTec\InputManager.h"

class Menu : public GameState
{
	inline void Start()
	{
		InputManager::Bind(IM_KEY_CODE::IM_KEY_F1, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { StateDirector::SetState(GameStateIdentifier::GAME_STATE_1); });
		InputManager::Bind(IM_KEY_CODE::IM_KEY_F2, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { StateDirector::SetState(GameStateIdentifier::GAME_STATE_2); });
	};

	inline void End() {};
	inline void Update(double DeltaTime) {};
	inline void Render(SDL_Renderer& renderer) {};
};

int main(int argc, char* argv[])
{
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_MAIN_MENU, new Menu());
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_1, new GameOfLife());
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_2, new LangtonsAnt());
	//StateDirector::SetState(GameStateIdentifier::GAME_STATE_MAIN_MENU);
	StateDirector::SetState(GameStateIdentifier::GAME_STATE_2);

	WindowDetails details;
	Game game;

	game.Initialise(argc, argv, details);

	if(game.GetIsInitialised())
	{
		game.Start();
	}

	return 0;
}