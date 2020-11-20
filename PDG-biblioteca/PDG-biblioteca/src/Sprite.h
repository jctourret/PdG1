#pragma once
#include "Exports.h"
#include "Entity.h"
#include "Texture.h"
#include "Animation.h"
#include "Timer.h"
#include <vector>
struct UV {
	float U;
	float V;
};
class SABASAENGINE_API Sprite : public Entity {
	int height;
	int width;
	int nrChannels;
	unsigned int texture;
	const char* _path;
	unsigned int vbo;
	unsigned int ebo;
	unsigned int vao;
	bool hasTransparecy;
	int currentFrame;
	int previousFrame;

	Texture* tex;
	Animation* anim;
	UV uv[4];
	unsigned int index[6] = {
	0, 1, 3,
	1, 2, 3
	};
	float vertex[32] = {
		1.0f,  1.0f, 0.0f,	1,1,1,  1, 1,
		1.0f, -1.0f, 0.0f,	1,1,1,  1, 0,
	   -1.0f, -1.0f, 0.0f,	1,1,1,  0,0,
	   -1.0f,  1.0f, 0.0f,	1,1,1,  0, 1
	};
public:
	Sprite(Renderer* renderer, bool transparency, const char* path);
	~Sprite();
	void setHeight(int height);
	int getHeight();
	void setWidth(int width);
	int getWidth();
	void setNrChanels(int nrChannels);
	int getNrChannels();
	void createVBO(float* vertex, int vertexAmmount);
	unsigned int getVBO();
	void createEBO(unsigned int* index, int indexAmmount);
	unsigned int getEBO();
	void createVAO();
	unsigned int getVAO();
	void setAnimation(Animation* animation);
	Animation* getAnimation();
	unsigned int getTexture();
	void bindTexture();
	void setAnimCoords(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3);
	void updateAnimation(Timer* time);
	void draw();
	void SetCurrentAnimationIndex(int currentAnimation);
};