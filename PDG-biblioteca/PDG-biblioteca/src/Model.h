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
