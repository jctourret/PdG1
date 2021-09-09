#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"


class SABASAENGINE_API Model : public Entity
{
public:
	string name;
	Model* parent;
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
	virtual void setRotation(vec3 newRot);
	virtual void setScale(vec3 newScale);
private:
};

