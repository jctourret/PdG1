#pragma once
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include "Exports.h"
#include "Renderer.h"

#include <string>
#include <vector>

using namespace std;

struct Vertex {
	glm::vec3 Position;
	glm::vec2 TexCoords;
	glm::vec3 Normal;
};

struct meshTexture {
	unsigned int id;
	string type;
	string path;
};

class SABASAENGINE_API Mesh
{
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
	float* vertexData;
	int* indicesData;	
public:
	vector<Vertex> _vertices;
	vector<unsigned int> _indices;
	vector<meshTexture> _textures;
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
		vector<meshTexture> textures, Renderer* rend);
	void drawMesh(Renderer* rend);
};


//#pragma once
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <vector>
//
//#include <assimp/types.h>
//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//
//using namespace glm;
//using namespace std;
//struct Vertex {
//	vec3 position;
//	vec3 normal;
//	vec2 texCoords;
//};
//struct Texture {
//	GLuint id;
//	string type;
//	aiString path;
//};
//class Mesh
//{
//	unsigned int VAO;
//	unsigned int VBO;
//	unsigned int EBO;
//	void setupMesh();
//public:
//	vector<Vertex> vertices;
//	vector<GLuint> indices;
//	vector<Texture> textures;
//
//	Mesh( vector<Vertex> newVertices, vector<GLuint> newIndices, vector<Texture> newTextures);
//	~Mesh();
//	void draw();
//};
//
