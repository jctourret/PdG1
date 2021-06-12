#pragma once
#include <glm/vec3.hpp>
#include "Exports.h"
#include "Renderer.h"

class SABASAENGINE_API Lightning
{
	Renderer* _rend;
	glm::vec3 _pos;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
public:
	Lightning(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer* rend);
	glm::vec3 getPos();
};