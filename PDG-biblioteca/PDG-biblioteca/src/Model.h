#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma);

class SABASAENGINE_API Model : public Entity
{
public:
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;
	Renderer* _rend;
	bool gammaCorrection;
	Model(Renderer* rend, bool gamma);
	void Draw();
private:
};

