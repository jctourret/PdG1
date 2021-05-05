#pragma once
#include "Exports.h"
#include "Window.h"
#include "Lightining.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>


class SABASAENGINE_API Renderer
{
private:
	GLuint _vertexShader;
	GLuint _fragmentShader;
	unsigned int _shaderProgram;
	Lightining _light;
	int _posAttrib;
	int _textureAttrib;
	int _normalAttrib;
public:
	void initVertexShader();
	void initFragmentShader();
	void initShaderProgram();
	void creatoVAO(unsigned int &vao);
	void createVBO(float* vertexDataArray, int arraySize, unsigned int &vbo);
	void createEBO(int* indexArray, int arraySize, unsigned int &_ebo);
	void setPosAttrib();
	void setTextureAttrib();
	void setNormalAttrib();
	void deleteShaderProgram();
	void deleteFragmentShader();
	void deleteVertexShader();
	void drawSprite(glm::mat4x4 trs, unsigned int vbo, unsigned int vao, float* vertex, unsigned int size, unsigned int indexSize);
	void setTexture(unsigned int texture);
	void bindSpriteBuffers(unsigned int vbo, unsigned int vao, float* vertex, float size);
	void setSpriteAttrib();
	void bindTexture(unsigned int texture);
	void startProgram(glm::mat4 model);
	void blendTexture();
	void unblendTexture();
	void setVP();
	void updateView(glm::vec3 position, glm::vec3 target);
	void updateView(glm::vec3 position, glm::vec3 front, glm::vec3 up);
};

