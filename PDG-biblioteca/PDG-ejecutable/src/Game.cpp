#include "Game.h"

Game::Game()
{
	
}

void Game::init()
{
	initBaseGame(1000, 500, "Awesome game");
	engineLoop();
}


Game ::~Game()
{
	
}

void Game::initGame()
{
	cout << "init" << endl;
}
void Game::updateGame()
{
	cout << "update" << endl;

}
void Game::destroyGame()
{
	cout << "destroy" << endl;

}
