#include "ReSprite.h"
#include "glm/gtc/type_ptr.hpp"

ReSprite::ReSprite(Renderer* renderer, const char* path) :Entity(renderer)
{
	rend = renderer;

	initSprite(path);

}
void ReSprite::initSprite(const char* path)
{
	const int vertexAmount = 20;
	const int indexAmount = 6;
	float verticesData[vertexAmount] = {
		-0.25f, 0.5f, 0.0f, 0.0f, 1.0f,
		-0.25f,-0.5f, 0.0f, 0.0f, 0.0f,
		 0.25f, 0.5f, 0.0f, 1.0f, 1.0f,
		 0.25f,-0.5f, 0.0f, 1.0f, 0.0f
	};
	width = 0.25 - (-0.25);
	height = 0.5 - (-0.5);

	int indicesData[indexAmount] =
	{
		0, 2, 3,
		1, 0, 3
	};
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* newTex = new Texture(path);
	newTex->Bind(0);
	texture = newTex->getTex();
	rend->setTexture(texture);
}

void ReSprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
	rend->drawShape(GL_QUADS, TRS, vbo, ebo);
}