#pragma once
#include "Window.h"
#include <vector>
class SABASAENGINE_API Renderer
{
private:
	GLuint* _vbo;
	GLuint _vertexShader;
	GLuint _fragmentShader;
	GLuint _shaderProgram;
	GLint _posAttrib;
	std::vector<GLfloat> _vertex;
public:
	Renderer();
	~Renderer();
	void initBuffer();
	void initVertexShader();
	void initFragmentShader();
	void initShaderProgram();
	void setPosAttrib();
	void addVertex(GLfloat vertexX, GLfloat vertexY);
	void deleteShaderProgram();
	void deleteFragmentShader();
	void deleteVertexShader();
	void deleteBuffer();
};

