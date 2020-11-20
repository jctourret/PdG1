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
		createTriangle();
	}
}
void Shape::createRectangle()
{
	const int vertexAmount = 20;
	const int indexAmount = 6;
	float verticesData[vertexAmount] = {
		-0.25f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.25f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.25f, 0.5f, 0.0f, 1.0f, 1.0f,
		 0.25f,-0.5f, 0.0f, 1.0f, 0.0f
	};
	width = 0.25f - (-0.25f);
	height = 0.5f - (-0.5f);
	int indicesData[indexAmount] =
	{
	    0, 2, 3,
		1, 0, 3
	};
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* texture = new Texture("../res/white.png");
	texture->Bind(0);
	defaultTexture = texture->getTex();
	rend->setTexture(defaultTexture);
}

void Shape::createTriangle()
{
	const int vertexAmount = 15;
	const int indexAmount = 3;
	float verticesData[vertexAmount] =
	{
			-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};
	int indicesData[indexAmount] =
	{
		0, 1, 2
	};
	width = 0.25f - (-0.25f);
	height = 0.5f - (-0.5f);
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData,indexAmount,ebo);
	Texture* texture = new Texture("../res/white.png");
	texture->Bind(0);
	defaultTexture = texture->getTex();
	rend->setTexture(defaultTexture);
}

void Shape::draw()
{
	glBindTexture(GL_TEXTURE_2D, defaultTexture);
	glActiveTexture(GL_TEXTURE0);
	rend->drawShape(_geometry, TRS, vbo, ebo);
}