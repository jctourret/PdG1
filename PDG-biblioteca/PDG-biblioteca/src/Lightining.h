#pragma once
#include <glm/vec3.hpp>
#include "Exports.h"

class SABASAENGINE_API Lightining
{
	glm::vec3 _pos;
public:
	Lightining();
	Lightining(glm::vec3 pos);
	glm::vec3 getPos();
	void setPos(glm::vec3 pos);
};