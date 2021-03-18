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
	float recVerticesData[20] = {
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,-0.5f, 0.0f, 1.0f, 0.0f
	};
	float triVerticesData[15] =
	{
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
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

