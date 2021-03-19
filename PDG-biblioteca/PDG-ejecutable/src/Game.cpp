#include "Game.h"

Game::Game()
{
	
}

Game ::~Game()
{
	
}

void Game::play()
{
	initBaseGame(1000, 500, "Puzzle Demo");
	engineLoop();
}

void Game::initGame(Renderer* renderer)
{
	timer = new Timer();
	timer->start();
	shapeA = new Shape(GL_QUADS, renderer);
	sprite1 = new Sprite(renderer, "res/spriteSheet.png",true);
	sprite2 = new Sprite(renderer, "res/Choclo.png", true);
	tileMap = new TileMap(renderer, 16, 16, "res/MasterSimple.png", 256, 256, 2.0f, 2.0f);
	_camera = new Camera(renderer);
	//automatizar, en vez de pasar id pasar una coordenada
	vector<int> tilemapLayout = /*{ 0,1,2,3,4,5,6,7,8,9,10,11,12 }; //*/{ 0,1,1,1,2,16,17,17,8 + 16 * 4,18,16,17,17,17,18,16,17,17,17,18,64,65,65,65,66};
	//automatizar, en vez de pasar id pasar una coordenada
	vector<bool> tilemapWalkable = { true,true, true, true, true, true, true, true, true, true, 
									true,true, true, true, true, true, true, true, true, true,
									true,true, true, true, true, true, true, true, true, true};
	tileMap->setTileMap(5,5,tilemapLayout,tilemapWalkable);
	animation = new Animation(); //spriteSheet 308 x 178
	
	//hacer un metodo que corte automaticamente 
	animation->addFrame(0.0f,				 0.0f,	102.66f, 89.0f, 308, 178);
	animation->addFrame((308 - 102.66f * 2), 0.0f,	102.66f, 89.0f, 308, 178);
	animation->addFrame((308 - 102.66f * 1), 0.0f,	102.66f, 89.0f, 308, 178);
	animation->addFrame(0.0f,				 89.0f, 102.66f, 89.0f, 308, 178);
	animation->addFrame((308 - 102.66f * 2), 89.0f, 102.66f, 89.0f, 308, 178);
	animation->addFrame((308 - 102.66f * 1), 89.0f, 102.66f, 89.0f, 308, 178);
	animation->addAnimation(0.5f);

	sprite1->setAnimation(animation);

	//HACER QUE SE SETEE VIEW Y PROJECTION Y ARREGLAR ESO DE QUE SE ROTAN MAL LAS COSAS Y ESO
	shapeA->setPosition(vec3(-1.0f, -1.0f, 0.5f));//shapeA->getPosition().x + shapeA->getScale().x * shapeA->width, 0.5f, 0.0f));
	shapeA->setRotation(vec3(0.0f, 0.0f, 0.0f));
	
	sprite1->setPosition(vec3(0.7f, -0.3f, 0.0f));
	sprite2->setPosition(vec3(-0.75, 1, 0.0f));
	sprite2->setScale(vec3(1, 2, 1));

	//hacer una animacion de fuego que freene el paso, un puzzle en el que empujas algo
	//y entra en un trigger y mientras esta en el trigger se apaga el fuego y podes pasar
	//si pasas hay un trigger que te muestra que ganaste


	//las collisiones no funcionan porque estan hechas con las medidas viejas
	//cuanddo arreglo lo de las medidas con la view se rompen los sprites, la animacion
	//mas que nada (opcion, cambiar el aspect ratio)

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
	if (input->isKeyDown(GLFW_KEY_KP_8))
	{
		camPosY ++;
	}
	if (input->isKeyDown(GLFW_KEY_KP_5))
	{
		camPosY--;
	}
	if (input->isKeyDown(GLFW_KEY_KP_4))
	{
		camPosX++;
	}
	if (input->isKeyDown(GLFW_KEY_KP_6))
	{
		camPosX--;
	}

	_camera->setPosition(glm::vec3 (camPosX,camPosY,camPosZ));

	vec3 movement = vec3(speedX, speedY, speedZ) * timer->getDT();

	vec3 newPos = shapeA->getPosition() + movement;
	shapeA->setPosition(newPos);

	vec3 newScale = shapeA->getScale() + vec3(growSpeed, growSpeed, growSpeed)*timer->getDT();
	shapeA->setScale(newScale);

	vec3 newRot = shapeA->getRotation() + vec3(rotXSpeed, rotYSpeed, rotZSpeed)*timer->getDT();
	shapeA->setRotation(newRot);


	if (collManager.CheckCollision(shapeA, sprite2)) cout << "Trigger!" << endl;
	collManager.CheckCollisionAgainstStatic(shapeA, sprite1, movement);

	tileMap->checkCollisionWithTileMap(shapeA, movement);

	timer->updateTimer();
	_camera->setTransform();
	sprite1->updateSprite(*timer);

	//draw
	tileMap->drawTileMap();
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
	if (tileMap) delete tileMap;
	if (animation) delete animation;
}
