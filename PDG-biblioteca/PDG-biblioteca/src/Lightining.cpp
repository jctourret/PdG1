#include "Lightining.h"

Lightining::Lightining(Renderer* rend) {
	_pos.x = 0.0f;
	_pos.y = 0.0f;
	_pos.z = -2.0f;
	_rend = rend;
}
Lightining::Lightining(glm::vec3 pos, Renderer* rend) {
	_pos = pos;
	_ambient = glm::vec3(1.0f, 1.0f, 1.0f);
	_diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	_specular = glm::vec3(1.0f, 1.0f, 1.0f);
	_rend = rend;
}
Lightining::Lightining(glm::vec3 pos, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, Renderer* rend) {
	_pos = pos;
	_ambient = ambient;
	_diffuse = diffuse;
	_specular = specular;
	_rend = rend;
	rend->updateLight(pos,ambient,diffuse,specular);
}
glm::vec3 Lightining::getPos() {
	return _pos;
}
void Lightining::setPos(glm::vec3 pos) {
	_pos = pos;
}

void Lightining::update(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
	_rend->updateLight(position,ambient,diffuse,specular);
}