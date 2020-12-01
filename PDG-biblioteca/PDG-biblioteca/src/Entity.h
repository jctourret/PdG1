#pragma once
#include "Renderer.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Exports.h"

using namespace glm;
using namespace std;
class SABASAENGINE_API Entity
{
protected:
	mat4 translateMat;
	mat4 rotateXMat;
	mat4 rotateYMat;
	mat4 rotateZMat;
	mat4 scaleMat;
	mat4 TRS;
	Renderer* rend;
	
	vec3 posVec;
	vec3 rotVec;
	vec3 scaleVec;

	void UpdateTRS();
public:
	Entity(Renderer* renderer);
	glm::vec3 getPosition();
	void setPosition(glm::vec3 newPosition);
	glm::vec3 getRotation();
	void setRotationX(float x);	//despues crear una funcion para setear 
	void setRotationY(float y);	//todas las rotaciones juntas
	void setRotationZ(float z); //
	void setRotation(glm::vec3 newRot);
	glm::vec3 getScale();
	void setScale(glm::vec3 newScale);
};

