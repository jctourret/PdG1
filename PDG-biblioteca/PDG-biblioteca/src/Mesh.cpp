#include "Mesh.h"

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices,
	vector<meshTexture> textures, Renderer* rend) {
	_vertices = vertices;
	_indices = indices;
	_textures = textures;
	vertexData = new float(_vertices.size()*sizeof(Vertex));
	indicesData = new int(_indices.size()*sizeof(unsigned int));
	rend->creatoVAO(vao);
	rend->createVBO(vertexData,_vertices.size(),vbo);
	rend->createEBO(indicesData, _indices.size(),ebo);
}

void Mesh::drawMesh(Renderer* rend) {
    // bind appropriate textures
    unsigned int diffuseNr = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr = 1;
    unsigned int heightNr = 1;
    for (unsigned int i = 0; i < _textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        string number;
        string name = _textures[i].type;
        if (name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if (name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to stream
        else if (name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to stream
        else if (name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to stream

        // now set the sampler to the correct texture unit
        glUniform1i(glGetUniformLocation(rend->getShaderProgram(), (name + number).c_str()), i);
        // and finally bind the texture
        glBindTexture(GL_TEXTURE_2D, _textures[i].id);
    }

    // draw mesh -> Preguntar a I�a
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

//#include "Mesh.h"
//
//
//
//
//Mesh::Mesh(vector<Vertex> newVertices, vector<GLuint> newIndices, vector<Texture> newTextures)
//{
//	vertices = newVertices;
//	indices = newIndices;
//	textures = newTextures;
//}
//
//
//Mesh::~Mesh()
//{
//}
//
//void Mesh::setupMesh()
//{
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
//	
//	//vertex positions
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)0);
//
//	//vertex normals
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex,normal));
//
//	//vertex normals
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *)offsetof(Vertex, texCoords));
//
//	glBindVertexArray(0);
//
//}
//
//void Mesh::draw()
//{
//	unsigned int diffuseN = 1;
//	unsigned int specularN = 1;
//
//	for (int i = 0; i < textures.size(); i++)
//	{
//		glActiveTexture(GL_TEXTURE0 + i);
//
//		stringstream ss;
//		string number;
//		string name = textures[i].type;
//
//		if ( "texture_diffuse" == name )
//		{
//			ss << diffuseN++;
//		}
//		else if ("texture_specular" == name)
//		{
//			ss << specularN;
//		}
//		number = ss.str();
//		//aca llamar a renderer
//		//glUniform1i(glGetUniformLocation(shaderProgram, (name + number).c_str()),i);
//		glBindTexture(GL_TEXTURE_2D, textures[i].id);
//	}
//
//	//glUniform1f(glGetUniformLocation(shaderProgram, "material.shininess"), 16.0f);
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//	for (int i = 0; i < textures.size(); i++)
//	{
//		glActiveTexture(GL_TEXTURE0 + i);
//		glBindTexture(GL_TEXTURE_2D, 0);
//	}
//}
