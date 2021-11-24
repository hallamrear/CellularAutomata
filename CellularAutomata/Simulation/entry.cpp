#include "GameOfLife.h"
#include "LangtonsAnt.h"
#include "Wireworld.h"
#include "HalTec\Game.h"
#include "HalTec\StateDirector.h"
#include "HalTec\InputManager.h"
#include "HalTec/TextElement.h"

class Menu : public GameState
{
	Transform transform;
	TextElement* mText;

	inline void Start()
	{
		mText = new TextElement(transform, "");

		InputManager::Bind(IM_KEY_CODE::IM_KEY_F1, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { StateDirector::SetState(GameStateIdentifier::GAME_STATE_1); });
		InputManager::Bind(IM_KEY_CODE::IM_KEY_F2, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { StateDirector::SetState(GameStateIdentifier::GAME_STATE_2); });
		InputManager::Bind(IM_KEY_CODE::IM_KEY_F3, IM_KEY_STATE::IM_KEY_PRESSED, [this]() { StateDirector::SetState(GameStateIdentifier::GAME_STATE_3); });
	};

	inline void End() { delete mText; mText = nullptr; };
	inline void Update(double DeltaTime) { mText->SetString("Press F1 for Conway's Game of Life. Press F2 for Langton's ant. Press F3 for Wireworld."); mText->Update(DeltaTime); };
	inline void Render(SDL_Renderer& renderer) { mText->Render(); };
};

int main(int argc, char* argv[])
{
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_MAIN_MENU, new Menu());
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_1, new GameOfLife());
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_2, new LangtonsAnt());
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_3, new Wireworld());
	StateDirector::SetState(GameStateIdentifier::GAME_STATE_MAIN_MENU);

	WindowDetails details;
	Game game;

	game.Initialise(argc, argv, details);

	if(game.GetIsInitialised())
	{
		game.Start();
	}

	return 0;
}