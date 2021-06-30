#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "stb_image.h"
#include "Entity.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include <vector>

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);

class SABASAENGINE_API Model : public Entity
{
public:
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;
	string directory;
	Renderer* _rend;
	bool gammaCorrection;
	Model(string const& path, Renderer* rend, bool gamma);
	void Draw();
private:
	void loadModel(string const& path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	vector<meshTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
};

