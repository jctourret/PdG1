#include "Game.h"
void main()
{
	Game* game = new Game();
	game->play();
	delete game;
}