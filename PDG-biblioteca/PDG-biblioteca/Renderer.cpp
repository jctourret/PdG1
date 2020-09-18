#include "Renderer.h"

const GLchar* vertexSource = R"glsl(
#version 150 core
in vec2 position;
void main()
{
gl_Position = vec4(position, 0.0, 1.0);
}
)glsl";
const GLchar* fragmentSource = R"glsl(
#version 150 core
out vec4 outColor;
void main()
{	
outColor = vec4(1.0, 1.0, 0.0, 1.0);
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

void Renderer::initBuffer() {
	glGenBuffers(1, _vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *_vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertex.size()*sizeof(GLfloat), &(_vertex[0]), GL_DYNAMIC_DRAW);
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
	glUseProgram(_shaderProgram);
}
void Renderer::setPosAttrib() {
	_posAttrib = glGetAttribLocation(_shaderProgram, "position");
	glVertexAttribPointer(_posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(_posAttrib);
}
void Renderer::addVertex(GLfloat vertexX, GLfloat vertexY) {
	_vertex.push_back(vertexX);
	_vertex.push_back(vertexY);
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