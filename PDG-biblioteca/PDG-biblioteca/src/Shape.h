#pragma once
#include "Entity.h"
#include "glm/mat4x4.hpp"
#include "Exports.h"
#include "Texture.h"

using namespace glm;

class SABASAENGINE_API Shape : public Entity
{
	unsigned int _geometry;
	void createRectangle();
	void createTriangle();
	void createCube();
	unsigned int vertexAmount = 20;
	unsigned int indexAmount = 6;
	float recVerticesData[20] = 
	{
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,-0.5f, 0.0f, 1.0f, 0.0f,
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f
	};
	float triVerticesData[15] =
	{
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};
	float cubeVerticesData[40] =
	{
		-0.5f,0.5f,-0.5f,   0.0f, 1.0f,//Point A 0
		-0.5f,0.5f,0.5f,    0.0f, 1.0f,//Point B 1
		0.5f,0.5f,-0.5f,    1.0f, 1.0f,//Point C 2
		0.5f,0.5f,0.5f,     1.0f, 1.0f,//Point D 3

		-0.5f,-0.5f,-0.5f,  0.0f, 0.0f,//Point E 4
		-0.5f,-0.5f,0.5f,   0.0f, 0.0f,//Point F 5
		0.5f,-0.5f,-0.5f,   1.0f, 0.0f,//Point G 6
		0.5f,-0.5f,0.5f,    1.0f, 0.0f,//Point H 7
	};
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int defaultTexture;
public:
	Shape(unsigned int geometry, Renderer* renderer);
	void draw();
	float width;
	float height;
};

