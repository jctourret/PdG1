#pragma once
#include "Entity2D.h"
#include "glm/mat4x4.hpp"
using namespace glm;

class Shape : public Entity
{
	unsigned int _geometry;
	void createRectangle();
	void createTriangle();
public:
	Shape(unsigned int geometry, Renderer* renderer);
	void Draw();
};

