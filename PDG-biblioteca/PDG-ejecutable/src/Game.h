#pragma once
#include "BaseGame.h"
class Game: BaseGame
{
public:
	Game();
	~Game();
	void init();
	void initGame() override;
	void updateGame() override;
	void destroyGame() override;
};