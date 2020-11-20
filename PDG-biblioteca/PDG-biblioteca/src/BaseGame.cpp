#include "BaseGame.h"
#include <iostream>
#include "Shape.h"
#include <glm/ext/matrix_clip_space.hpp>

using namespace std;

BaseGame::BaseGame()
{
	window = new Window();
	renderer = new Renderer();
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
}

int BaseGame::engineLoop()
{
	Shape* triangle = new Shape(GL_TRIANGLES, renderer);
	//Shape* square = new Shape(GL_QUADS, renderer);
	
	renderer->initVertexShader();
	renderer->initFragmentShader();
	renderer->initShaderProgram();
	renderer->setPosAttrib();
	renderer->setTextureAttrib();
	//renderer->proy = mat4(1.0f);
	//renderer->proy = ortho(-2.0f,2.0f,-1.5f,1.5f,-1.0f,1.0f);
	//renderer->view = mat4(1.0f);
	//renderer->view = lookAt(vec3(0.0f, 0.0f, -1.0f), vec3(0.0f, 0.0f, 1.0f), vec3(0.0f, 1.0f, 0.0f));
	float speedX = 0;
	float speedY = 0;
	float speedZ = 0;
	float growSpeed = 0;
	float rotXSpeed = 0;
	float rotYSpeed = 0;
	float rotZSpeed = 0;
	float deltaTime = 0;
	float lastTimer=glfwGetTime();


	while (!glfwWindowShouldClose(window->getWindow()) && !gameShouldClose)
	{
		//clear
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		deltaTime = glfwGetTime() - lastTimer;
		lastTimer = glfwGetTime();
		//input
		if (glfwGetKey(window->getWindow(),GLFW_KEY_UP)==GLFW_PRESS)
		{
			speedY = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS)
		{
			speedY = -1;
		}
		else
		{
			speedY = 0;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS)
		{
			speedX = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS)
		{
			speedX = -1;
		}
		else
		{
			speedX = 0;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_L) == GLFW_PRESS)
		{
			speedZ = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_O) == GLFW_PRESS)
		{
			speedZ = -1;
		}
		else
		{
			speedZ = 0;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_U) == GLFW_PRESS)
		{
			growSpeed = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_J) == GLFW_PRESS)
		{
			growSpeed = -1;
		}
		else
		{
			growSpeed = 0;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_S) == GLFW_PRESS)
		{
			rotXSpeed = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_W) == GLFW_PRESS)
		{
			rotXSpeed = -1;
		}
		else
		{
			rotXSpeed = 0;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_A) == GLFW_PRESS)
		{
			rotYSpeed = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_D) == GLFW_PRESS)
		{
			rotYSpeed = -1;
		}
		else
		{
			rotYSpeed = 0;
		}

		if (glfwGetKey(window->getWindow(), GLFW_KEY_Q) == GLFW_PRESS)
		{
			rotZSpeed = 1;
		}
		else if (glfwGetKey(window->getWindow(), GLFW_KEY_E) == GLFW_PRESS)
		{
			rotZSpeed = -1;
		}
		else
		{
			rotZSpeed = 0;
		}
		
		if (glfwGetKey(window->getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			gameShouldClose = true;
		}

		vec3 newPos = triangle->getPosition() + vec3(speedX,speedY,speedZ) * deltaTime;
		triangle->setPosition(newPos);
		
		vec3 newScale = triangle->getScale() + vec3(growSpeed, growSpeed, growSpeed)*deltaTime;
		triangle->setScale(newScale);

		vec3 newRot = triangle->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*deltaTime;
		triangle->setRotation(newRot);

		//draw
		triangle->Draw();
		//square->Draw();
		//swap
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
	renderer->deleteShaderProgram();
	renderer->deleteFragmentShader();
	renderer->deleteVertexShader();
	renderer->deleteBuffer();
	glfwTerminate();

	return 0;
}
