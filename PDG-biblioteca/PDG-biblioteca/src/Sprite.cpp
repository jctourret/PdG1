#include "GL/glew.h";
#include "GLFW/glfw3.h";
#include "sprite.h"
#include "stb_image.h"

Sprite::Sprite(Renderer* renderer, bool transparency, const char* path) :Entity(Entity::rend) 
{
	tex = new Texture(path);
	tex->Bind(0);
	texture = tex->getTex();
	int vertSize = 32;

	createVAO();
	createEBO(index, 6);
	createVBO(vertex, vertSize);

	hasTransparecy = transparency;
	uv[0].U = 0.0f; uv[0].V = 0.0f;
	uv[1].U = 0.0f; uv[1].V = 0;
	uv[2].U = 0;    uv[2].V = 0;
	uv[3].U = 0;    uv[3].V = 0.0f;

}

Sprite::~Sprite() 
{
	glDeleteTextures(1, &texture);
	if (tex)
	{
		delete tex;
	}
	if (anim) 
	{
		delete anim;
	}
}

void Sprite::setHeight(int height) {
	height = height;
}
int Sprite::getHeight() {
	return height;
}
void Sprite::setWidth(int width) {
	width = width;
}
int Sprite::getWidth() {
	return width;
}
void Sprite::setNrChanels(int nrChannels) {
	nrChannels = nrChannels;
}
int Sprite::getNrChannels() {
	return nrChannels;
}
void Sprite::createVBO(float* vertex, int vertexAmmount) {
	int vertexSize = sizeof(vertex) * vertexAmmount;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertex, GL_STATIC_DRAW);
}
unsigned int Sprite::getVBO() {
	return vbo;
}

void Sprite::createEBO(unsigned int* index, int indexAmmount) {
	unsigned int indexSize = sizeof(index) * indexAmmount;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexSize, index, GL_STATIC_DRAW);
}
unsigned int Sprite::getEBO() {
	return ebo;
}
void Sprite::createVAO() {
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}
unsigned int Sprite::getVAO() {
	return vao;
}
void Sprite::setAnimation(Animation* animation) {
	anim = animation;
	previousFrame = std::numeric_limits<unsigned int>::max_digits10;
}
Animation* Sprite::getAnimation() {
	return anim;
}

unsigned int Sprite::getTexture() {
	return texture;
}

void Sprite::bindTexture() {
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
}

void Sprite::setAnimCoords(float u0, float v0, float u1, float v1, float u2, float v2, float u3, float v3) {
	vertex[6] = u0;   vertex[7] = v0;
	vertex[14] = u1;  vertex[15] = v1;
	vertex[22] = u2;  vertex[23] = v2;
	vertex[30] = u3;  vertex[31] = v3;

}
void Sprite::updateAnimation(Timer* time) {
	if (anim != NULL) {
		anim->update(time);
		currentFrame = anim->getCurrentFrame();

		if (currentFrame != previousFrame) {
			setAnimCoords(anim->getAnimation()[currentFrame].coordinates[0].U, anim->getAnimation()[currentFrame].coordinates[0].V,
				anim->getAnimation()[currentFrame].coordinates[3].U, anim->getAnimation()[currentFrame].coordinates[3].V,
				anim->getAnimation()[currentFrame].coordinates[2].U, anim->getAnimation()[currentFrame].coordinates[2].V,
				anim->getAnimation()[currentFrame].coordinates[1].U, anim->getAnimation()[currentFrame].coordinates[1].V);
			previousFrame = currentFrame;
		}
		setAnimation(anim);
	}
}

void Sprite::draw() {
	if (hasTransparecy) {
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		rend->setTexture(texture);
		rend->drawShape(GL_QUADS, TRS, vbo, ebo);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
	}
	else {
		rend->setTexture(texture);
		rend->drawShape(GL_QUADS, TRS, vbo, ebo);
		glDisable(GL_TEXTURE_2D);
	}
}

void Sprite::SetCurrentAnimationIndex(int currentAnimation) {
	if (anim != NULL) anim->setAnimNum(currentAnimation);
}