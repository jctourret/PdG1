#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Timer.h"
#include "CollisionManager.h"
class SABASAENGINE_API BaseGame
{
private:
	Window* window;
	Renderer* renderer;
	CollisionManager collManager;
	bool gameShouldClose;
public:
	BaseGame();
	~BaseGame();
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop();
	virtual void initGame() = 0;
	virtual void updateGame() = 0;
	virtual void destroyGame() = 0;
};