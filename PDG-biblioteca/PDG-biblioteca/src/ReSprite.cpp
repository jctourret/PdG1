#include "ReSprite.h"
#include "glm/gtc/type_ptr.hpp"

ReSprite::ReSprite(Renderer* renderer, const char* path) :Entity(renderer)
{
	rend = renderer;

	initSprite(path);

}
void ReSprite::initSprite(const char* path)
{
	width = 0.25 - (-0.25);
	height = 0.5 - (-0.5);
	rend->creatoVAO(vao);
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	Texture* newTex = new Texture(path);
	newTex->Bind(0);
	texture = newTex->getTex();
	rend->setTexture(texture);
}

void ReSprite::UpdateSprite(Timer & timer) {
	if (!_animation) {
		return;
	}
	_animation->update(timer);
	_currentFrame = _animation->getCurrentFrame();
	if (_currentFrame != _prevFrame
		|| _currentFrame == _animation->getAnimation().size()-1
		|| _currentFrame == 0) {
		SetTextureCoordinates(
			_animation->getAnimation()[_currentFrame].coordinates[1].U, _animation->getAnimation()[_currentFrame].coordinates[1].V,
			_animation->getAnimation()[_currentFrame].coordinates[2].U, _animation->getAnimation()[_currentFrame].coordinates[2].V,
			_animation->getAnimation()[_currentFrame].coordinates[3].U, _animation->getAnimation()[_currentFrame].coordinates[3].V,
			_animation->getAnimation()[_currentFrame].coordinates[0].U, _animation->getAnimation()[_currentFrame].coordinates[0].V
		);
		_prevFrame = _currentFrame;
	}
	setAnimation(_animation);
}
void ReSprite::SetTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
{
	verticesData[3] = u0;
	verticesData[8] = u1;
	verticesData[13] = u2;
	verticesData[18] = u3;
	
	verticesData[4] = v0;
	verticesData[9] = v1;
	verticesData[14] = v2;
	verticesData[19] = v3;
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), verticesData, GL_STATIC_DRAW);
}
void ReSprite::draw()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
	rend->drawSprite(GL_QUADS, TRS, vbo, ebo, vao, verticesData, vertexAmount);
}