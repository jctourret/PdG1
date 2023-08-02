#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Frustum.h"
#include "Plane.h"
#include "Model.h"
#include <array>

#define BOX_VERTEX 8

class Model;

class SABASAENGINE_API BoundingBox : Entity
{
private:
	bool isBeingRendered;

	vec3 center{ 0.f, 0.f, 0.f };
	vec3 extents{ 0.f, 0.f, 0.f };


public:
	BoundingBox();
	bool isOutOfFrustum(vector<Plane*> planes, Entity* inEntity);
	BoundingBox(const vec3& min, const vec3& max);
	BoundingBox(const Model* model, bool includeChildren);
	//Sending this parameters as 3 floats because we already have a 2 vec3 constructor
	BoundingBox(const vec3 inCenter, float inExtentX, float inExtentY, float inExtentZ);
	
	bool isOnOrForwardPlane(Plane* plane);
	bool isOnOrBackwardsPlane(Plane* plane);
	bool isOnFrustum(vector<Plane*> planes,Entity* inEntity);
	const array<vec3, BOX_VERTEX> getVertice();
	
	void UpdateModel(); //?
	vec3 GetMaxVector();
	vec3 GetMinVector();


};


/*


std::array<glm::vec3, 8> getVertice() const
{
	std::array<glm::vec3, 8> vertice;
	vertice[0] = { center.x - extents.x, center.y - extents.y, center.z - extents.z };
	vertice[1] = { center.x + extents.x, center.y - extents.y, center.z - extents.z };
	vertice[2] = { center.x - extents.x, center.y + extents.y, center.z - extents.z };
	vertice[3] = { center.x + extents.x, center.y + extents.y, center.z - extents.z };
	vertice[4] = { center.x - extents.x, center.y - extents.y, center.z + extents.z };
	vertice[5] = { center.x + extents.x, center.y - extents.y, center.z + extents.z };
	vertice[6] = { center.x - extents.x, center.y + extents.y, center.z + extents.z };
	vertice[7] = { center.x + extents.x, center.y + extents.y, center.z + extents.z };
	return vertice;
}

//see https://gdbooks.gitbooks.io/3dcollisions/content/Chapter2/static_aabb_plane.html
bool isOnOrForwardPlane(const Plane& plane) const final
{
	// Compute the projection interval radius of b onto L(t) = b.c + t * p.n
	const float r = extents.x * std::abs(plane.normal.x) + extents.y * std::abs(plane.normal.y) +
		extents.z * std::abs(plane.normal.z);

	return -r <= plane.getSignedDistanceToPlane(center);
}

bool isOnFrustum(const Frustum& camFrustum, const Transform& transform) const final
{
	//Get global scale thanks to our transform
	const glm::vec3 globalCenter{ transform.getModelMatrix() * glm::vec4(center, 1.f) };

	// Scaled orientation
	const glm::vec3 right = transform.getRight() * extents.x;
	const glm::vec3 up = transform.getUp() * extents.y;
	const glm::vec3 forward = transform.getForward() * extents.z;

	const float newIi = std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 1.f, 0.f, 0.f }, forward));

	const float newIj = std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 1.f, 0.f }, forward));

	const float newIk = std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, right)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, up)) +
		std::abs(glm::dot(glm::vec3{ 0.f, 0.f, 1.f }, forward));

	const AABB globalAABB(globalCenter, newIi, newIj, newIk);

	return (globalAABB.isOnOrForwardPlane(camFrustum.leftFace) &&
		globalAABB.isOnOrForwardPlane(camFrustum.rightFace) &&
		globalAABB.isOnOrForwardPlane(camFrustum.topFace) &&
		globalAABB.isOnOrForwardPlane(camFrustum.bottomFace) &&
		globalAABB.isOnOrForwardPlane(camFrustum.nearFace) &&
		globalAABB.isOnOrForwardPlane(camFrustum.farFace));
};*/