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
	unsigned int vbo;
	unsigned int ebo;
	unsigned int defaultTexture;
public:
	Shape(unsigned int geometry, Renderer* renderer);
	void draw();
	float width;
	float height;
};

