#pragma once
#include "Exports.h"
#include "Window.h"
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <vector>

class SABASAENGINE_API Renderer
{
private:
	GLuint* _vbo;
	GLuint _vertexShader;
	GLuint _fragmentShader;
	unsigned int _shaderProgram;
	int _posAttrib;
	std::vector<float> _vertex;  //dejar privado en la funcion de add vertex
	void initBuffer();
public:
	Renderer();
	~Renderer();
	void initVertexShader();
	void initFragmentShader();
	void initShaderProgram();
	void setPosAttrib();
	void addVertexes(float* vertexDataArray,int arraySize);
	void deleteShaderProgram();
	void deleteFragmentShader();
	void deleteVertexShader();
	void deleteBuffer();
	void drawShape();
	unsigned int getShader();
};

