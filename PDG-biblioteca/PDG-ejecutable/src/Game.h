#pragma once
#include "BaseGame.h"
class Game: BaseGame
{
	bool gameShouldClose = false;
	Shape* shapeA;
	ReSprite* sprite1;
	ReSprite* sprite2;
	Timer* timer;
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;
	float growSpeed = 0;
	float rotXSpeed = 0;
	float rotYSpeed = 0;
	float rotZSpeed = 0;
public:
	Game();
	~Game();
	void init();
	void initGame(Renderer* renderer) override;
	void updateGame(Window* window, CollisionManager collManager, Renderer* renderer, Input* input) override;
	void destroyGame() override;
};