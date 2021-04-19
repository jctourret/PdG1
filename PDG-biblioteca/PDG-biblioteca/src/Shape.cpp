#include "Shape.h"
#include "glm/gtc/type_ptr.hpp"

Shape::Shape(unsigned int geometry, Renderer* renderer):Entity(renderer)
{
	rend = renderer;
	_geometry = geometry;
	
	if (_geometry == GL_QUADS)
	{
		createRectangle();
	}
	else
	{
		//createTriangle();
		createCube();
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

		/*Above ABC,BCD*/
		0,1,2,
		1,2,3,

		/*Following EFG,FGH*/
		4,5,6,
		5,6,7,
		/*Left ABF,AEF*/
		0,1,5,
		0,4,5,
		/*Right side CDH,CGH*/
		2,3,7,
		2,6,7,
		/*ACG,AEG*/
		0,2,6,
		0,4,6,
		/*Behind BFH,BDH*/
		1,5,7,
		1,3,7

	};
	rend->creatoVAO(vao);
	rend->createVBO(cubeVerticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* texture = new Texture("res/white.png");
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
	rend->creatoVAO(vao);
	rend->createVBO(recVerticesData, vertexAmount, vbo);
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
	rend->creatoVAO(vao);
	rend->createVBO(triVerticesData, vertexAmount, vbo);
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
	if (_geometry == GL_QUADS)
	{
		rend->drawSprite(TRS, vbo, vao, recVerticesData, vertexAmount, indexAmount); //
	}
	else
	{
		rend->drawSprite(TRS, vbo, vao, cubeVerticesData, vertexAmount, indexAmount); //
	}
}