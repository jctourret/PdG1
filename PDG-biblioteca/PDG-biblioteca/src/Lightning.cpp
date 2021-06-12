#include "Lightning.h"

Lightning::Lightning(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer* rend) {
	_pos = pos;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_rend = rend;
	rend->updateLight(pos, ambient, diffuse, specular);
}
glm::vec3 Lightning::getPos() {
	return _pos;
}