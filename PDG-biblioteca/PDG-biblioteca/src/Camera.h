#pragma once
#include "Exports.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include "Renderer.h"

class SABASAENGINE_API Camera
{
protected:
	glm::vec3 _position;
	glm::vec3 _target;
	glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
	Renderer* _renderer;
public:
	Camera(Renderer* rend);
	~Camera();
	void setTransform();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void move(glm::vec3 movement);
	void setTarget(glm::vec3 position);
	glm::vec3 getTarget();
};

