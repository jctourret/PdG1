#pragma once
#include "BaseGame.h"
class Game: BaseGame
{
private:
	Timer* timer;
	Shape* shapeA;
	Sprite* sprite1;
	Sprite* sprite2;
	Animation* animation;
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
	void play();
	void initGame(Renderer* renderer) override;
	void updateGame(CollisionManager collManager, Input* input) override;
	void destroyGame() override;
};