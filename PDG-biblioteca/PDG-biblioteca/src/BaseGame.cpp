#include "BaseGame.h"
#include <iostream>
#include "Shape.h"
#include "Sprite.h"
#include "ReSprite.h"
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
	Timer* timer = new Timer();
	timer->start();
	Shape* shapeA = new Shape(GL_QUADS, renderer);
	ReSprite* test = new ReSprite(renderer, "../res/TRS.png");
	//Sprite* sprite1 = new Sprite(renderer,true, "../res/TRS.png");

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

	shapeA->setPosition(vec3(shapeA->getPosition().x + shapeA->getScale().x * shapeA->width,0.0f,0.0f));
	cout << shapeA->getPosition().x << endl;
	cout << shapeA->getPosition().y << endl;
	cout << shapeA->getPosition().z << endl;
	//shapeA->setPosition();
	while (!glfwWindowShouldClose(window->getWindow()) && !gameShouldClose)
	{
		//clear
		glClearColor(1.0f, 0.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
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

		cout << collManager.CheckCollision(shapeA, test);

		vec3 newPos = shapeA->getPosition() + vec3(speedX, speedY, speedZ) * timer->getDT();
		shapeA->setPosition(newPos);
		
		vec3 newScale = shapeA->getScale() + vec3(growSpeed, growSpeed, growSpeed)*timer->getDT();
		shapeA->setScale(newScale);

		vec3 newRot = shapeA->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*timer->getDT();
		shapeA->setRotation(newRot);

		timer->updateTimer();

		//draw
		shapeA->draw();
		test->draw();

		//swap
		glfwSwapBuffers(window->getWindow());
		glfwPollEvents();
	}
	renderer->deleteShaderProgram();
	renderer->deleteFragmentShader();
	renderer->deleteVertexShader();
	glfwTerminate();

	return 0;
}
