#include "Game.h"
#include "glm/glm.hpp"
Game::Game()
{
	
}

Game ::~Game()
{
	
}

void Game::init()
{
	initBaseGame(1000, 500, "Awesome Game");
	engineLoop();
}

void Game::initGame(Renderer* renderer)
{
	timer = new Timer();
	timer->start();
	shapeA = new Shape(GL_QUADS, renderer);
	sprite1 = new ReSprite(renderer, "../res/TRS.png");
	sprite2 = new ReSprite(renderer, "../res/Choclo.png");

	renderer->initVertexShader();
	renderer->initFragmentShader();
	renderer->initShaderProgram();
	renderer->setPosAttrib();
	renderer->setTextureAttrib();

	shapeA->setPosition(vec3(shapeA->getPosition().x + shapeA->getScale().x * shapeA->width, 0.0f, 0.0f));
	sprite2->setPosition(vec3(-0.75f, 0.5f, 0.0f));
}
void Game::updateGame(Window* window, CollisionManager collManager, Renderer* renderer, Input* input)
{
	//input
	if (input->isKeyDown(GLFW_KEY_UP))
	{
		speedY = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_DOWN))
	{
		speedY = -1;
	}
	else
	{
		speedY = 0;
	}

	if (input->isKeyDown(GLFW_KEY_RIGHT))
	{
		speedX = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_LEFT))
	{
		speedX = -1;
	}
	else
	{
		speedX = 0;
	}

	if (input->isKeyDown(GLFW_KEY_L))
	{
		speedZ = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_O))
	{
		speedZ = -1;
	}
	else
	{
		speedZ = 0;
	}

	if (input->isKeyDown(GLFW_KEY_U))
	{
		growSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_J))
	{
		growSpeed = -1;
	}
	else
	{
		growSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_S))
	{
		rotXSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_W))
	{
		rotXSpeed = -1;
	}
	else
	{
		rotXSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_A))
	{
		rotYSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_D))
	{
		rotYSpeed = -1;
	}
	else
	{
		rotYSpeed = 0;
	}

	if (input->isKeyDown(GLFW_KEY_Q))
	{
		rotZSpeed = 1;
	}
	else if (input->isKeyDown(GLFW_KEY_E))
	{
		rotZSpeed = -1;
	}
	else
	{
		rotZSpeed = 0;
	}

	vec3 movement = vec3(speedX, speedY, speedZ) * timer->getDT();

	vec3 newScale = shapeA->getScale() + vec3(growSpeed, growSpeed, growSpeed)*timer->getDT();
	shapeA->setScale(newScale);
	vec3 newRot = shapeA->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*timer->getDT();
	shapeA->setRotation(newRot);

	vec3 newPos = shapeA->getPosition() + movement;
	shapeA->setPosition(newPos);

	if (collManager.CheckCollision(shapeA, sprite2)) cout << "Trigger!" << endl;
	collManager.CheckCollisionAndReact(shapeA, sprite1, movement);

	timer->updateTimer();

	//draw
	shapeA->draw();
	sprite1->draw();
	sprite2->draw();

}
void Game::destroyGame()
{
	if (shapeA)	delete shapeA;
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;
	if (timer) delete timer;
}
