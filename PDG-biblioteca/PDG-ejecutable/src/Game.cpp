#include "Game.h"

Game::Game()
{
	
}

Game ::~Game()
{
	
}

void Game::play()
{
	initBaseGame(1000, 500, "Awesome game");
	engineLoop();
}

void Game::initGame(Renderer* renderer)
{
	timer = new Timer();
	timer->start();
	shapeA = new Shape(GL_QUADS, renderer);
	sprite1 = new ReSprite(renderer, "../res/spriteSheet.png",true);
	sprite2 = new ReSprite(renderer, "../res/Choclo.png",true);
	animation = new Animation(); //spriteSheet 308 x 178

	animation->addFrame(0.0f,				 0.0f,	102.66f, 89.0f, 308, 178, 0.5f);
	animation->addFrame((308 - 102.66f * 2), 0.0f,	102.66f, 89.0f, 308, 178, 0.5f);
	animation->addFrame((308 - 102.66f * 1), 0.0f,	102.66f, 89.0f, 308, 178, 0.5f);
	animation->addFrame(0.0f,				 89.0f, 102.66f, 89.0f, 308, 178, 0.5f);
	animation->addFrame((308 - 102.66f * 2), 89.0f, 102.66f, 89.0f, 308, 178, 0.5f);
	animation->addFrame((308 - 102.66f * 1), 89.0f, 102.66f, 89.0f, 308, 178, 0.5f);
	animation->addAnimation();

	sprite1->setAnimation(animation);

	shapeA->setPosition(vec3(shapeA->getPosition().x + shapeA->getScale().x * shapeA->width, 0.0f, 0.0f));
	sprite2->setPosition(vec3(-0.75f, 0.5f, 0.0f));
	cout << shapeA->getPosition().x << endl;
	cout << shapeA->getPosition().y << endl;
	cout << shapeA->getPosition().z << endl;
}
void Game::updateGame(CollisionManager collManager, Input* input)
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

	vec3 newPos = shapeA->getPosition() + movement;
	shapeA->setPosition(newPos);

	vec3 newScale = shapeA->getScale() + vec3(growSpeed, growSpeed, growSpeed)*timer->getDT();
	shapeA->setScale(newScale);

	vec3 newRot = shapeA->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*timer->getDT();
	shapeA->setRotation(newRot);

	if (collManager.CheckCollision(shapeA, sprite2)) cout << "Trigger!" << endl;
	collManager.CheckCollisionAgainstStatic(shapeA, sprite1, movement);

	timer->updateTimer();

	sprite1->UpdateSprite(*timer);

	//draw
	shapeA->draw();
	sprite1->draw();
	sprite2->draw();


}
void Game::destroyGame()
{
	if (timer) delete timer;
	if (shapeA) delete shapeA;
	if (sprite1) delete sprite1;
	if (sprite2) delete sprite2;
	if (animation) delete animation;
}
