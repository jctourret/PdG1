#include "Camera.h"


Camera::Camera(Renderer* rend)
{
	_renderer = rend;
	_position = glm::vec3(0.0f, 0.0f, 0.0f);
	_target = glm::vec3(0.0f, 0.0f, 0.0f);
}

Camera::~Camera(){

}

void Camera::setTransform(){
	_renderer->updateView(_position,_target);
}

void Camera::setPosition(glm::vec3 position) {
	_position = position;
	setTransform();
}

glm::vec3 Camera::getPosition() {
	return _position;
}

void Camera::move(glm::vec3 movement)
{
	_position += movement;
	setTransform();
}


void Camera::setTarget(glm::vec3 target) {
	_target = target;
}

glm::vec3 Camera::getTarget() {
	return _target;
}