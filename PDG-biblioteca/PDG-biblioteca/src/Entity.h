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
	Entity();
	Entity(Renderer* renderer);
	vec3 getPosition();
	virtual void setPosition(vec3 newPosition);
	vec3 getRotation();
	virtual void setRotationX(float x);	//despues crear una funcion para setear 
	virtual void setRotationY(float y);	//todas las rotaciones juntas
	virtual void setRotationZ(float z);
	virtual void setRotation(vec3 newRot);
	vec3 getScale();
	virtual void setScale(vec3 newScale);
	mat4 getTRS();
};
