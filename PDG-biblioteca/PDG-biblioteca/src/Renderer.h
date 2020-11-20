#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

class SABASAENGINE_API Renderer
{
private:
//	GLuint* _vbo;
	GLuint _vertexShader;
	GLuint _fragmentShader;
	unsigned int _shaderProgram;
	int _posAttrib;
	void initBuffer(std::vector<float> _vertex);
	
public:
	Renderer();
	~Renderer();
	void initVertexShader();
	void initFragmentShader();
	void initShaderProgram();
	void createVBO(float* vertexDataArray, int arraySize, unsigned int &_vbo);
	void createEBO(int* indexArray, int arraySize, unsigned int &_ebo);
	void setPosAttrib();
	void setTextureAttrib();
	void addVertexes(float* vertexDataArray,int arraySize);
	void deleteShaderProgram();
	void deleteFragmentShader();
	void deleteVertexShader();
	void deleteBuffer();
	void drawShape(unsigned int geometry, glm::mat4x4 trs, unsigned int _vbo, unsigned int ebo);
	void setTexture();
	unsigned int getShader();
};

