#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
using namespace std;
using namespace glm;

const GLchar* vertexSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoor;
out vec2 texCoord;
uniform mat4 MVP;
void main()
{
gl_Position = MVP * vec4(position, 1.0);
texCoord = texCoor;
}
)glsl";

const GLchar* fragmentSource = R"glsl(
#version 330 core
out vec4 outColor;
in vec2 texCoord;
uniform sampler2D tex;
void main()
{	
vec4 texColor = texture(tex, texCoord);
outColor = texColor;
}
)glsl";

Renderer::Renderer() {
	_vbo = new GLuint();
}

Renderer::~Renderer() {
	if (_vbo != NULL) {
		delete _vbo;
	}
}

void Renderer::initBuffer(std::vector<float> _vertex) {
	glGenBuffers(1, _vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *_vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertex.size() * sizeof(GLfloat), &(_vertex[0]), GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float) + 8 * sizeof(int), &(_vertex[0]), GL_STATIC_DRAW);
}

void Renderer::initVertexShader() {
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(_vertexShader);

}
void Renderer::initFragmentShader() {
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(_fragmentShader);
}

void Renderer::initShaderProgram() {
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);
	glValidateProgram(_shaderProgram);
	//unsigned int transformLoc = glGetUniformLocation(shader, "transform");
	//unsigned int projectionLoc = glGetUniformLocation(shader, "projection");
	//unsigned int viewLoc = glGetUniformLocation(shader, "view");
	
	glUseProgram(_shaderProgram);
	//glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(model));
	//glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(proj));
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
}

void Renderer::setPosAttrib() {
	_posAttrib = glGetAttribLocation(_shaderProgram, "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void Renderer::setTextureAttrib()
{
	int _textureAttrib = glGetAttribLocation(_shaderProgram, "texCoor");
	glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
}

void Renderer::addVertexes(float* vertexDataArray, int arraySize)
{
	std::vector<float> _vertex;
	for (int i = 0; i < arraySize; i++)
	{
		_vertex.push_back(vertexDataArray[i]);
	}
	initBuffer(_vertex);
}

void Renderer::deleteShaderProgram() {
	glDeleteProgram(_shaderProgram);
}

void Renderer::deleteFragmentShader() {
	glDeleteShader(_fragmentShader);
}

void Renderer::deleteVertexShader() {
	glDeleteShader(_vertexShader);
}

void Renderer::deleteBuffer() {
	glDeleteBuffers(1, _vbo);
}

void Renderer::drawShape(unsigned int geometry)
{
	//glBindVertexArray(_posAttrib); //?
	if (geometry == GL_TRIANGLES)
	{
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
	else
	{
		glDrawArrays(GL_QUADS, 0, 4);
	}
	//glBindVertexArray(0);
	//glUseProgram(0);
}

unsigned int Renderer::getShader()
{
	return _shaderProgram;
}
