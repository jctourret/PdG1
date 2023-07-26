#pragma once
#include "Exports.h"
#include <glm/vec3.hpp>
#include "Plane.h"
#include "Camera.h"

class Camera;

class SABASAENGINE_API Frustum
{
public:
	Frustum(Camera* cam, float aspect, float fovY, float zNear, float zFar);
	bool pointInFrustum(glm::vec3 position);
	~Frustum();
	Plane topFace;
	Plane bottomFace;

	Plane rightFace;
	Plane leftFace;

	Plane farFace;
	Plane nearFace;
private:
};

