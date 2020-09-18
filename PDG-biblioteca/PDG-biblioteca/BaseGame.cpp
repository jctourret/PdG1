#include "BaseGame.h"
#include <iostream>
using namespace std;

BaseGame::BaseGame()
{
	window = new Window();
	renderer = new Renderer();
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
	//if (!glfwInit()) hacer alguna manera de checkear que inicializó
	//	return -1;
	window->createWindow(screenWidth, screenHeight, title);
	//checkear que se cree la window:
	/*
	if (!window->checkWindowCreation())
	{
		cout << "che no abrió, que onda?";
		cin.get();
		glfwTerminate();
		return -1;
	}
	*/
	glfwMakeContextCurrent(window->getWindow());
	glewExperimental = GL_TRUE;
	glewInit();
}

int BaseGame::update()
{
	//GLFWwindow* window;

	/* Create a windowed mode window and its OpenGL context */
	//window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);
	//if (!window)
	//{
	//	cout << "esto tampoco abrio vieja";
	//	cin.get();
	//	glfwTerminate();
	//	return -1;
	//}

	renderer->addVertex(0.0f, 0.5f);
	renderer->addVertex(0.5f, 0.5f);
	renderer->addVertex(0.5f, -0.5f);
	renderer->addVertex(-0.5f, -0.5f);

	renderer->initBuffer();
	renderer->initVertexShader();
	renderer->initFragmentShader();
	renderer->initShaderProgram();
	renderer->setPosAttrib();

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window->getWindow()))
	{
		/* Render here */
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_QUADS, 0, 4);
		/* Swap front and back buffers */
		glfwSwapBuffers(window->getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}
	renderer->deleteShaderProgram();
	renderer->deleteFragmentShader();
	renderer->deleteVertexShader();
	renderer->deleteBuffer();
	glfwTerminate();

	return 0;
}
