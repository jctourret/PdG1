#pragma once
#include <glm/vec3.hpp>
#include "Exports.h"
#include "Renderer.h"

class SABASAENGINE_API Lightining
{
	glm::vec3 _pos;
	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	Renderer* _rend;
public:
	Lightining(Renderer* rend);
	Lightining(glm::vec3 pos, Renderer* rend);
	Lightining(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer* rend);
	glm::vec3 getPos();
	void setPos(glm::vec3 pos);
	void update(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular);
};