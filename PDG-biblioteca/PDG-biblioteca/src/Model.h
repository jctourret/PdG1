#pragma once

#include "Exports.h"
#include "Texture.h"
#include "Mesh.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <string>

unsigned int TextureFromFile(const char* path, const string& directory);

class SABASAENGINE_API Model
{
public:
    // model data 
    vector<meshTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
    vector<Mesh> meshes;
    string directory;
    Model(string const& path, Renderer* rend);
    void loadModel(string const& path, Renderer* rend);
    void Draw(Renderer* rend);
    void processNode(aiNode* node, const aiScene* scene, Renderer* rend);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene, Renderer* rend);
    vector<meshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
//#pragma once
//
//#include <string>
//#include <fstream>
//#include <sstream>
//#include <iostream>
//#include <map>
//#include <vector>
//
//#include <GL/glew.h>
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <assimp/Importer.hpp>
//#include <assimp/scene.h>
//#include <assimp/postprocess.h>
//
//#include "stb_image.h" //sacar cuando uses tu propia clase texture 
//
//#include "Mesh.h"
//
//using namespace std;
//using namespace glm;
//
//GLint TextureFromFile(const char *path, string directory);
//
//class Model
//{
//	vector<Mesh>meshes;
//	string directory;
//	vector<Texture> textures_loaded;
//	void loadModel(string path);
//	void processNode(aiNode *node, const aiScene *scene);
//	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
//	vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
//public:
//	Model(GLchar *path);
//	~Model();
//
//	void draw();
//};
//
