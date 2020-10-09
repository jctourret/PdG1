#pragma once
#include "Exports.h"
#include "Renderer.h"
class SABASAENGINE_API BaseGame
{
private:
	Window* window;
	Renderer* renderer;
	bool gameShouldClose;
public:
	BaseGame();
	~BaseGame();
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int engineLoop();
};