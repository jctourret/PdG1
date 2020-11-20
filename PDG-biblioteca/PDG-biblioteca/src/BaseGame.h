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
	Timer time;
	CollisionManager collManager;
	bool gameShouldClose;
public:
	BaseGame();
	~BaseGame();
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop();
};