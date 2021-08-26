#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"


class SABASAENGINE_API Model : public Entity
{
public:
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;
	vector<Model*> children;
	Renderer* _rend;
	bool gammaCorrection;
	bool hasSpecularMaps;
	Model(Renderer* rend, bool gamma);
	void Draw();
	void AddChild(Model* newChild);
	virtual void setPosition(vec3 newPosition);
private:
};

