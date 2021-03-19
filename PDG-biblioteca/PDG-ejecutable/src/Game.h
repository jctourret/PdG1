#pragma once
#include "BaseGame.h"
class Game: BaseGame
{
private:
	Timer* timer;
	Shape* shapeA;
	Sprite* sprite1;
	Sprite* sprite2;
	TileMap* tileMap;
	Animation* animation;
	Camera* _camera;
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;
	float growSpeed = 0;
	float rotXSpeed = 0;
	float rotYSpeed = 0;
	float rotZSpeed = 0;

	float camPosX = 0.0f;
	float camPosY = 0.0f;
	float camPosZ = 1.0f;

	float camTargetX = 0.0f;
	float camTargetY = 0.0f;
	float camTargetZ = 0.0f;
public:
	Game();
	~Game();
	void play();
	void initGame(Renderer* renderer) override;
	void updateGame(CollisionManager collManager, Input* input) override;
	void destroyGame() override;
};