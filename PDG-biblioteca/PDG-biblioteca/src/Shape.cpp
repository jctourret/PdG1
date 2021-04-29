#include "Shape.h"
#include "glm/gtc/type_ptr.hpp"

Shape::Shape(ShapeTypes shapeType, Renderer* renderer):Entity(renderer)
{
	rend = renderer;
	_shapeType = shapeType;
	vertexToUse = NULL;
	switch (_shapeType)
	{
	case triangle:
		createTriangle();
		break;
	case cube:
		createCube();
		break;
	default:
	case rectangle:
		createRectangle();
		break;
	}
}

void Shape::createCube()
{
	vertexAmount = 40;
	indexAmount = 36;
	width = 0.25f - (-0.25f);
	height = 0.5f - (-0.5f);
	int indicesData[36] =
	{
		0,1,2,
		1,2,3,
	
		4,5,6,
		5,6,7,
		
		0,1,5,
		0,4,5,
		
		2,3,7,
		2,6,7,
		
		0,2,6,
		0,4,6,
		
		1,5,7,
		1,3,7
	};
	vertexToUse = cubeVerticesData;
	rend->creatoVAO(vao);
	rend->createVBO(vertexToUse, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* texture = new Texture("res/Choclo.png");
	texture->Bind(0);
	defaultTexture = texture->getTex();
	rend->setTexture(defaultTexture);
}

void Shape::createRectangle()
{
	vertexAmount = 20;
	indexAmount = 6;
	width = 0.25f - (-0.25f);
	height = 0.5f - (-0.5f);
	int indicesData[6] =
	{
	    0, 1, 3,
		1, 2, 3
	};
	vertexToUse = recVerticesData;
	rend->creatoVAO(vao);
	rend->createVBO(vertexToUse, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* texture = new Texture("res/white.png");
	texture->Bind(0);
	defaultTexture = texture->getTex();
	rend->setTexture(defaultTexture);
}

void Shape::createTriangle()
{
	vertexAmount = 15;
	indexAmount = 3;
	int indicesData[3] =
	{
		0, 1, 2
	};
	width = 0.25f - (-0.25f);
	height = 0.5f - (-0.5f);
	vertexToUse = triVerticesData;
	rend->creatoVAO(vao);
	rend->createVBO(vertexToUse, vertexAmount, vbo);
	rend->createEBO(indicesData,indexAmount,ebo);
	Texture* texture = new Texture("res/white.png");
	texture->Bind(0);
	defaultTexture = texture->getTex();
	rend->setTexture(defaultTexture);
}

void Shape::draw()
{
	glBindTexture(GL_TEXTURE_2D, defaultTexture);
	glActiveTexture(GL_TEXTURE0);

	rend->drawSprite(TRS, vbo, vao, vertexToUse, vertexAmount, indexAmount); 
}