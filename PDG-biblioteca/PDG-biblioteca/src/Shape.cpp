#include "Shape.h"
#include "glm/gtc/type_ptr.hpp"
#include "Texture.h"

Shape::Shape(unsigned int geometry, Renderer* renderer):Entity(renderer)
{
	rend = renderer;
	_geometry = geometry;
	
	if (_geometry == GL_QUADS)
	{
		createRectangle();
	}
	else
	{
		createTriangle();
	}
}
Texture* tex;
void Shape::createRectangle()
{
	const int vertexAmount = 20;
	float vertexesData[vertexAmount] = {
		-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
		 0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
		 0.5f,-0.5f, 0.0f, 1.0f, 0.0f
	};
	rend->addVertexes(vertexesData,vertexAmount);

	tex = new Texture("../res/TRS.png");
	tex->Bind(0);
	unsigned int shader = rend->getShader();
	unsigned int uniformTex = glGetUniformLocation(shader, "Tex");
	glUseProgram(shader);
	glUniform1i(uniformTex, 0);
}

void Shape::createTriangle()
{
	const int vertexAmount = 15;

	float vertexesData[vertexAmount] = {
			-0.5f,-0.5f, 0.0f, 0.0f, 0.0f,
			 0.0f, 0.5f, 0.0f, 0.5f, 1.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
	};
	rend->addVertexes(vertexesData, vertexAmount);

	tex = new Texture("../res/TRS.png");
	tex->Bind(0);
	unsigned int shader = rend->getShader();
	unsigned int uniformTex = glGetUniformLocation(shader, "Tex");
	glUseProgram(shader);
	glUniform1i(uniformTex, 0);
}

void Shape::Draw()
{
	unsigned int shader = rend->getShader();
	
	unsigned int uniformModel = glGetUniformLocation(shader, "MVP");
	glUseProgram(shader);
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(TRS));
	rend->drawShape(_geometry);
}