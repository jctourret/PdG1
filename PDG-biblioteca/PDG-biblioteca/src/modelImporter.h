#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Model.h"
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class SABASAENGINE_API modelImporter
{
	string directory;
protected:

public:
	~modelImporter();
	vector<Model*> models_Loaded;
	void loadModel(string const& path, Renderer* rend);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	vector<meshTexture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};

