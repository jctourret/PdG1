#include "Sprite.h"
#include "glm/gtc/type_ptr.hpp"

Sprite::Sprite(Renderer* renderer, const char* path,bool transparency) :Entity(renderer)
{
	rend = renderer;
	initSprite(path);
	_transparency = transparency;
}
void Sprite::initSprite(const char* path)
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

void Sprite::UpdateSprite(Timer & timer) {
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
void Sprite::SetTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
{
	verticesData[3] = u0;
	verticesData[8] = u1;
	verticesData[13] = u2;
	verticesData[18] = u3;
	
	verticesData[4] = v0;
	verticesData[9] = v1;
	verticesData[14] = v2;
	verticesData[19] = v3;
	
	rend->bindSpriteBuffers(vbo, vao, verticesData, 20);
}
void Sprite::draw()
{
	if (_transparency) {
		blendSprite();
	}
	rend->bindTexture(texture);
	rend->drawSprite(TRS, vbo, vao, verticesData, vertexAmount);
	if (_transparency) {
		unblendSprite();
	}
}

void Sprite::blendSprite() {
	rend->blendTexture();
}

void Sprite::unblendSprite() {
	rend->unblendTexture();
}