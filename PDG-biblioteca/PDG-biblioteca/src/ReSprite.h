#pragma once
#include "Entity.h"
#include "glm/mat4x4.hpp"
#include "Exports.h"
#include "Texture.h"

using namespace glm;

class SABASAENGINE_API ReSprite : public Entity
{
	void initSprite(const char* path);
	unsigned int vbo;
	unsigned int ebo;
	unsigned int texture;
public:
	ReSprite(Renderer* renderer, const char* path);
	void draw();
	float width;
	float height;
};