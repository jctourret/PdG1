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

	glUseProgram(_shaderProgram);
}

void Renderer::createVBO(float* vertexDataArray, int arraySize, unsigned int &vbo)
{
	std::vector<float> _vertex;
	for (int i = 0; i < arraySize; i++)
	{
		_vertex.push_back(vertexDataArray[i]);
	}
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertex.size() * sizeof(GLfloat), &(_vertex[0]), GL_STATIC_DRAW);
}

void Renderer::createEBO(int* indexArray, int arraySize, unsigned int &_ebo) 
{
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray) * arraySize, indexArray, GL_STATIC_DRAW);
}

void Renderer::setPosAttrib() 
{
	_posAttrib = glGetAttribLocation(_shaderProgram, "position");
	glVertexAttribPointer(_posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
}

void Renderer::setTextureAttrib()
{
	_textureAttrib = glGetAttribLocation(_shaderProgram, "texCoor");
	glVertexAttribPointer(_textureAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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

void Renderer::drawShape(unsigned int geometry, glm::mat4x4 trs, unsigned int vbo, unsigned int ebo)
{
	glUseProgram(_shaderProgram);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glEnableVertexAttribArray(_posAttrib);
	glEnableVertexAttribArray(_textureAttrib);
	

	unsigned int uniformModel = glGetUniformLocation(_shaderProgram, "MVP");
	glBindVertexArray(_posAttrib);


	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(trs));
	
	if (geometry == GL_TRIANGLES)
	{
		glDrawElements(geometry, 3, GL_UNSIGNED_INT, 0);
	}
	else
	{
		glDrawElements(geometry, 6, GL_UNSIGNED_INT, 0);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Renderer::setTexture(unsigned int texture)
{
	unsigned int uniformTex = glGetUniformLocation(_shaderProgram, "tex");
	glUseProgram(_shaderProgram);
	glUniform1i(uniformTex, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
}
