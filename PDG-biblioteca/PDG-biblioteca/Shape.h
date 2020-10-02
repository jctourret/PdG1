#pragma once
#include "Entity2D.h"
class Shape : Entity2D
{
private:
	float defaultDistance;
public:
	void createRec(vec2 position);
	void createRec(vec2 position, float width, float height);
};

