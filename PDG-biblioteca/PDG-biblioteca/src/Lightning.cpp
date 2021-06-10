#include "Lightning.h"

Lightning::Lightning(glm::vec3 pos, Renderer* renderer) {
	_pos = pos;
	rend = renderer;
	rend->setLightUniformData(pos);
}

glm::vec3 Lightning::getPos() {
	return _pos;
}

void Lightning::setPos(glm::vec3 pos) {
	_pos = pos;
	rend->setLightUniformData(pos);
}