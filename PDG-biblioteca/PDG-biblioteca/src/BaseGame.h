#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Timer.h"
#include "CollisionManager.h"
#include "Input.h"
#include "Shape.h"
#include "Sprite.h"
#include "TileMap.h"
#include "Camera.h"
class SABASAENGINE_API BaseGame
{
private:
	Window* window;
	Renderer* renderer;
	CollisionManager collManager;
	Input* input;
	bool gameShouldClose;
public:
	BaseGame();
	~BaseGame();
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop();
	virtual void initGame(Renderer* renderer) = 0;
	virtual void updateGame(CollisionManager collManager,Input* input) = 0;
	virtual void destroyGame() = 0;
};