#include "Simulation.h"
#include "HalTec\Game.h"
#include "HalTec\StateDirector.h"

int main(int argc, char* argv[])
{
	StateDirector::SetupState(GameStateIdentifier::GAME_STATE_PLAYING, new Simulation());
	StateDirector::SetState(GameStateIdentifier::GAME_STATE_PLAYING);

	WindowDetails details;
	Game game;

	game.Initialise(argc, argv, details);

	if(game.GetIsInitialised())
	{
		game.Start();
	}

	return 0;
}