#pragma once
#include "Exports.h"
#include "Renderer.h"
#include "Mesh.h"
#include "Entity.h"
#include "BoundingBox.h"

class BoundingBox;

class SABASAENGINE_API Model : public Entity
{
public:
	string name;
	vec3 globalPos;
	Model* parent;
	vector<meshTexture> textures_loaded;
	vector<Mesh> meshes;
	vector<Model*> children;
	Renderer* _rend;
	bool gammaCorrection;
	bool hasSpecularMaps;
	Model(Renderer* rend, bool gamma);
	~Model();
	void Draw();
	void UpdateTRS() override;
	void AddChild(Model* newChild);
	virtual void setPosition(vec3 newPosition);
	virtual void setRotation(vec3 newRot);
	virtual void setScale(vec3 newScale);
	BoundingBox* collectiveBBox;
	BoundingBox* individualBBox;
private:
};

