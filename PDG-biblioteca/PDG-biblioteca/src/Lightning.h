#pragma once
#include <glm/vec3.hpp>
#include "Exports.h"
#include "Renderer.h"

enum LightType
{
	test,
	point,
	directional,
	spot
};

class SABASAENGINE_API Lightning
{
	Renderer* _rend;
	glm::vec3 _pos;
	glm::vec3 _dir;

	glm::vec3 _ambient;
	glm::vec3 _diffuse;
	glm::vec3 _specular;
	
	float _constant;
	float _linear;
	float _quadratic;
	
	float _cutOff;

	LightType _lightType;
public:
	Lightning(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, LightType lightType, Renderer* rend);
	glm::vec3 getPos();
};