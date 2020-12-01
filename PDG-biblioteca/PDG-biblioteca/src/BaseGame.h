#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Timer.h"
#include "Input.h"
#include "CollisionManager.h"
class SABASAENGINE_API BaseGame
{
private:
	Window* window;
	Renderer* renderer;
	Input* input;
	CollisionManager collManager;
	bool gameShouldClose;
public:
	BaseGame();
	~BaseGame();
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop();
	virtual void initGame(Renderer* renderer) = 0;
	virtual void updateGame(Window* window, CollisionManager collManager, Renderer* renderer, Input* input) = 0;
	virtual void destroyGame() = 0;
};