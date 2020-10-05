#pragma once
#include "Entity.h"
#include "glm/mat4x4.hpp"
#include "Exports.h"

using namespace glm;

class SABASAENGINE_API Shape : public Entity
{
	unsigned int _geometry;
	void createRectangle();
	void createTriangle();
public:
	Shape(unsigned int geometry, Renderer* renderer);
	void Draw();
};

