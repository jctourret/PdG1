#include "Sprite.h"
#include "glm/gtc/type_ptr.hpp"

Sprite::Sprite(Renderer* renderer, const char* path,bool transparency) :Entity(renderer)
{
	rend = renderer;
	initSprite(path);
	_transparency = transparency;
	textureUsed = NULL;
}
Sprite::Sprite(Renderer* renderer, unsigned int newTexture, bool transparency) :Entity(renderer)
{
	rend = renderer;
	initSprite(newTexture);
	_transparency = transparency;
	textureUsed = NULL;
}
Sprite::Sprite(Renderer* renderer, unsigned int newTexture, bool transparency, float newWidth, float newHeight) :Entity(renderer)
{
	rend = renderer;
	initSprite(newTexture,newWidth,newHeight);
	_transparency = transparency;
	textureUsed = NULL;
}
Sprite::~Sprite()
{
	if (textureUsed) delete textureUsed;
}
void Sprite::initSprite(const char* path)
{
	width =  baseWidth;
	height = baseHeight;
	rend->creatoVAO(vao);
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	textureUsed = new Texture(path);
	textureUsed->Bind(0);
	texture = textureUsed->getTex();
	rend->setTexture(texture);
}
void Sprite::initSprite(unsigned int newTexture)
{
	width = baseWidth;
	height = baseHeight;
	rend->creatoVAO(vao);
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	texture = newTexture;
	rend->setTexture(texture);
}
void Sprite::initSprite(unsigned int newTexture, float scaleX, float scaleY)
{
	_scaleX = scaleX;
	_scaleY = scaleY;

	verticesData[0] = (0 + (baseWidth / 2)) * _scaleX;
	verticesData[1] = (0 + (baseHeight / 2)) * _scaleY;

	verticesData[5] = (0 + (baseWidth / 2)) * _scaleX;
	verticesData[6] = (0 - (baseHeight / 2)) * _scaleY;

	verticesData[10] = (0 - (baseWidth / 2)) * _scaleX;
	verticesData[11] = (0 - (baseHeight / 2)) * _scaleY;

	verticesData[15] = (0 - (baseWidth / 2)) * _scaleX;
	verticesData[16] = (0 + (baseHeight / 2)) * _scaleY;
	
	width = verticesData[0] - verticesData[10];
	height = verticesData[1] - verticesData[11];

	rend->creatoVAO(vao);
	rend->createVBO(verticesData, vertexAmount, vbo);
	rend->createEBO(indicesData, indexAmount, ebo);
	texture = newTexture;
	rend->setTexture(texture);
}

void Sprite::updateSprite(Timer & timer) {
	if (!_animation) {
		return;
	}
	_animation->update(timer);
	_currentFrame = _animation->getCurrentFrame();
	if (_currentFrame != _prevFrame
		|| _currentFrame == _animation->getAnimation().size()-1
		|| _currentFrame == 0) {
		setTextureCoordinates(
			_animation->getAnimation()[_currentFrame].coordinates[1].U, _animation->getAnimation()[_currentFrame].coordinates[1].V,
			_animation->getAnimation()[_currentFrame].coordinates[2].U, _animation->getAnimation()[_currentFrame].coordinates[2].V,
			_animation->getAnimation()[_currentFrame].coordinates[3].U, _animation->getAnimation()[_currentFrame].coordinates[3].V,
			_animation->getAnimation()[_currentFrame].coordinates[0].U, _animation->getAnimation()[_currentFrame].coordinates[0].V
		);
		_prevFrame = _currentFrame;
	}
	setAnimation(_animation);
}

void Sprite::setTextureCoordinates(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3)
{
	verticesData[3] = u0;
	verticesData[8] = u1;
	verticesData[13] = u2;
	verticesData[18] = u3;
	

	verticesData[4] = v0;
	verticesData[9] = v1;
	verticesData[14] = v2;
	verticesData[19] = v3;
	/*
	cout<<	verticesData[3]	<<endl;
	cout<<	verticesData[8]	<<endl;
	cout<<	verticesData[13]<<endl;
	cout<<	verticesData[18]<<endl<<endl;
	cout<<	verticesData[4]	<<endl;
	cout<<	verticesData[9]	<<endl;
	cout<<	verticesData[14]<<endl;
	cout<<	verticesData[19]<<endl;
	cin.get();
	*/

	rend->bindSpriteBuffers(vbo, vao, verticesData, 20);
}

void Sprite::draw()
{
	if (_transparency) {
		blendSprite();
	}
	rend->bindTexture(texture);
	rend->drawSprite(TRS, vbo, vao, verticesData, vertexAmount, indexAmount);
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