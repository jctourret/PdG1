#pragma once
#include "Exports.h"
#include "Shape.h"
#include "ReSprite.h"
#include "glm/glm.hpp"

struct Collider
{
	float width;
	float height;
	vec3 pos;
	vec3 scale;
};

struct CollisionResult
{
	bool left;
	bool right;
	bool top;
	bool bottom;
};

class SABASAENGINE_API CollisionManager
{
	Collider a;
	Collider b;
	CollisionResult result;
	bool isColliding();
public:
	bool CheckCollision(Shape* shapeA, Shape* ShapeB);
	bool CheckCollision(Shape* shape, ReSprite* sprite);
	bool CheckCollision(ReSprite* spriteA, ReSprite* spriteB);
	bool CheckCollisionAndReact(Shape* shape, ReSprite* sprite, bool firstOneReacts);
};