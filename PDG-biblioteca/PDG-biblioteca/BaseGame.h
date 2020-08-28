#pragma once
#include "Exports.h"
#include "Window.h"
class SABASAENGINE_API BaseGame
{
private:
	Window* window;
public:
	BaseGame();
	~BaseGame();
	void initBaseGame(int screenWidth, int screenHeight, const char* title);
	int update();
};