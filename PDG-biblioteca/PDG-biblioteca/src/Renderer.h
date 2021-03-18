#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>


class SABASAENGINE_API Renderer
{
private:
	GLuint _vertexShader;
	GLuint _fragmentShader;
	unsigned int _shaderProgram;
	int _posAttrib;
	int _textureAttrib;

public:
	void initVertexShader();
	void initFragmentShader();
	void initShaderProgram();
	void creatoVAO(unsigned int &vao);
	void createVBO(float* vertexDataArray, int arraySize, unsigned int &vbo);
	void createEBO(int* indexArray, int arraySize, unsigned int &_ebo);
	void setPosAttrib();
	void setTextureAttrib();
	void deleteShaderProgram();
	void deleteFragmentShader();
	void deleteVertexShader();
	void drawSprite(glm::mat4x4 trs, unsigned int vbo, unsigned int vao, float* vertex, unsigned int size);
	void setTexture(unsigned int texture);
	void bindSpriteBuffers(unsigned int vbo, unsigned int vao, float* vertex, float size);
	void setSpriteAttrib();
	void bindTexture(unsigned int texture);
	void startProgram(glm::mat4 model);
	void blendTexture();
	void unblendTexture();
	void setVP();
};

