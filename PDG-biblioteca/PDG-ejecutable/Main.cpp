#include "Game.h"
void main()
{
	Game* game = new Game();
	game->init();
	delete game;
}