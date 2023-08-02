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
	BoundingBox(const vec3& min, const vec3& max);
	BoundingBox(const Model* model, bool includeChildren);
	//Sending this parameters as 3 floats because we already have a 2 vec3 constructor
	BoundingBox(const vec3 inCenter, float inExtentX, float inExtentY, float inExtentZ);
	
	bool isOnOrForwardPlane(Plane plane);
	bool isOnFrustum(Frustum* camFrustum, Entity* inEntity);
	const array<vec3, BOX_VERTEX> getVertice();
	
	vec3 GetMaxVector();
	vec3 GetMinVector();


};