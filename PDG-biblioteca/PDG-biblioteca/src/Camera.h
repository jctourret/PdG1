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
	Renderer* _renderer;
public:
	Camera(Renderer* rend);
	~Camera();
	void setTransform();
	void setPosition(glm::vec3 position);
	glm::vec3 getPosition();
	void setTarget(glm::vec3 position);
	glm::vec3 getTarget();
};

