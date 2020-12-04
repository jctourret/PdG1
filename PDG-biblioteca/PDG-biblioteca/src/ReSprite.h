#pragma once
#include "Entity.h"
#include "glm/mat4x4.hpp"
#include "Exports.h"
#include "Texture.h"
#include "Animation.h"
#include "Timer.h"

using namespace glm;


class SABASAENGINE_API ReSprite : public Entity
{
	const int vertexAmount = 20;
	const int indexAmount = 6;
	void initSprite(const char* path);
	float verticesData[20] = {
		 0.25f, 0.5f, 0.0f, 1.0f, 1.0f,	//arriba der
		 0.25f,-0.5f, 0.0f, 1.0f, 0.0f,	 //abajo der
		-0.25f,-0.5f, 0.0f, 0.0f, 0.0f,	 //abajo izq
		-0.25f, 0.5f, 0.0f, 0.0f, 1.0f, //arriba izq
	};
	int indicesData[6] =
	{
		0, 1, 3,
		1, 2, 3
	};
	unsigned int vbo;
	unsigned int vao;
	unsigned int ebo;
	unsigned int texture;
	int _currentFrame;
	int _prevFrame;
	Animation* _animation;
	bool _transparency;
public:
	ReSprite(Renderer* renderer, const char* path,bool transparency);
	void draw();
	void UpdateSprite(Timer& timer);
	void setAnimation(Animation* animation) { _animation = animation; }
	void SetTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);
	float width;
	float height;
	void blendSprite();
	void unblendSprite();
};