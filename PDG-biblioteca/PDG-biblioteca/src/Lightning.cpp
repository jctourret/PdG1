#include "Lightning.h"

Lightning::Lightning(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, LightType lightType, Renderer* rend) 
{
	_pos = pos;
	_dir = dir;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_lightType = lightType;
	_rend = rend;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_cutOff = cutOff;
	_rend->updateLight(_pos, dir, _ambient, _diffuse, _specular, _constant, _linear, _quadratic, _cutOff, static_cast<unsigned int>(_lightType));
}
glm::vec3 Lightning::getPos() 
{
	return _pos;
}