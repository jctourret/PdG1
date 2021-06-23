#include "Lightning.h"

int Lightning::dirLights = 0;
int Lightning::pointLights = 0;
int Lightning::spotLights = 0;

Lightning::Lightning(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, LightType lightType, Renderer* rend) 
{
	_lightType = lightType;
	
	switch (_lightType)
	{
	case test:
		id = 0;
		break;
	case point:
		id = pointLights++;
		break;
	case directional:
		id = dirLights++;
		break;
	case spot:
		id = spotLights++;
		break;
	default:
		id = 0;
		break;
	}

	_pos = pos;
	_dir = dir;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_rend = rend;
	_constant = constant;
	_linear = linear;
	_quadratic = quadratic;
	_cutOff = cutOff;
	_rend->updateLight(_pos, dir, _ambient, _diffuse, _specular, _constant, _linear, _quadratic, _cutOff, static_cast<unsigned int>(_lightType), id);
}
glm::vec3 Lightning::getPos() 
{
	return _pos;
}