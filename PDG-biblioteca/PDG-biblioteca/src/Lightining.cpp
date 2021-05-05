#include "Lightining.h"

Lightining::Lightining() {
	_pos.x = 0.0f;
	_pos.y = 0.0f;
	_pos.z = -2.0f;
}
Lightining::Lightining(glm::vec3 pos) {
	_pos = pos;
}
glm::vec3 Lightining::getPos() {
	return _pos;
}
void Lightining::setPos(glm::vec3 pos) {
	_pos = pos;
}