#include "Shape.h"
#include "glm/gtc/type_ptr.hpp"

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

void Shape::createRectangle()
{
	float vertexesData[12] = {
		-0.5f,-0.5f,0.0f,
		-0.5f,0.5f,0.0f,
		0.5f,0.5f,0.0f,
		0.5f,-0.5f,0.0f
	};
	rend->addVertexes(vertexesData,12);
}

void Shape::createTriangle()
{
	float vertexesData[9] = {
	-0.5f,-0.5f,0.0f,
	0.0f, 0.5f , 0.0f,
	0.5f,-0.5f,0.0f
	};
	rend->addVertexes(vertexesData, 9);
}

void Shape::Draw()
{
	unsigned int shader = rend->getShader();
	unsigned int uniformModel = glGetUniformLocation(shader, "MVP");
	glUseProgram(shader);
	glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(TRS));
	rend->drawShape(_geometry);
}