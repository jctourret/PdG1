#pragma once
#include "Exports.h"
#include <iostream>
#include <glm/vec3.hpp>
#include <glm/mat2x2.hpp>
class SABASAENGINE_API Plane
{
	// unit vector
	
	// distance from origin to the nearest point in the plane
	float     distance = 0.f;
public:
	glm::vec3 normal = { 0.f, 1.f, 0.f };
	Plane();
	~Plane();
	Plane(const glm::vec3& p1, const glm::vec3& norm)
	{
		normal = glm::normalize(norm);
		distance = glm::dot(normal, p1);
		std::cout << "Normal: " << normal.x << " " << normal.y << " " << normal.z << std::endl;
	};
	Plane GetReversedPlane();

	float getSignedDistanceToPlane(const glm::vec3& point)
	{
		return glm::dot(normal, point) - distance;
	};
};

