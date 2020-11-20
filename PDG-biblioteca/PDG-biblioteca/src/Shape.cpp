#include "Shape.h"
#include "glm/gtc/type_ptr.hpp"
#include "Texture.h"

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
//Texture* tex;
void Shape::createRectangle()
{
	const int vertexAmount = 20;
	const int indexAmount = 6;
	float verticesData[vertexAmount] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,-0.5f, 0.0f, 1.0f, 0.0f
	};
	int indicesData[indexAmount] =
	{
	    0, 2, 3,
		1, 0, 3
	};
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* texturaTest = new Texture("../res/TRS.png");
	texturaTest->Bind(0);
	rend->setTexture();
	//tex = new Texture("../res/TRS.png");
	//tex->Bind(0);
	//unsigned int shader = rend->getShader();
	//unsigned int uniformTex = glGetUniformLocation(shader, "Tex");
	//glUseProgram(shader);
	//glUniform1i(uniformTex, 0);
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
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData,indexAmount,ebo);
	Texture* texturaTest = new Texture("../res/TRS.png");
	texturaTest->Bind(0);
	rend->setTexture();
	//Texture* tex = new Texture("../res/Choclo.png");
	//tex->Bind(0);
}

void Shape::Draw()
{
	rend->drawShape(_geometry, TRS, vbo, ebo);
}