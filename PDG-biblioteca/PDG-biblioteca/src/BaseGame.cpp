#include "BaseGame.h"
#include <iostream>
#include "Shape.h"
#include "ReSprite.h"
#include <glm/ext/matrix_clip_space.hpp>

using namespace std;

BaseGame::BaseGame()
{
	window = new Window();
	renderer = new Renderer();
	input = new Input(window);
	gameShouldClose = false;
}

BaseGame::~BaseGame()
{
	if (window != NULL) {
		delete window;
	}
	if (renderer != NULL) {
		delete renderer;
	}
}

void BaseGame::initBaseGame(int screenWidth, int screenHeight, const char* title)
{
	glfwInit();
	window->createWindow(screenWidth, screenHeight, title);
	glfwMakeContextCurrent(window->getWindow());
	glewExperimental = GL_TRUE;
	glewInit();
	initGame(renderer);
}

int BaseGame::engineLoop()
{
	while (!glfwWindowShouldClose(window->getWindow()) && !gameShouldClose)
	{
		//clear
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		updateGame(window, collManager,renderer,input);
		
		if (input->isKeyDown(GLFW_KEY_ESCAPE))
		{
			gameShouldClose = true;
		}
		//swap
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
	destroyGame();

	renderer->deleteShaderProgram();
	renderer->deleteFragmentShader();
	renderer->deleteVertexShader();
	glfwTerminate();

	return 0;
}
