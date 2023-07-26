#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION

Model::Model(Renderer* rend, bool gamma) : gammaCorrection(gamma), Entity(rend)
{
	_rend = rend;
	parent = NULL;
	globalPos = vec3(0);
}

Model::~Model()
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]) delete children[i];
	}
	if (individualBBox) delete individualBBox;
	if (collectiveBBox) delete collectiveBBox;
}

void Model::UpdateTRS()
{
	TRS = translateMat * rotateXMat * rotateYMat * rotateZMat * scaleMat;
	if(parent)
	{
		TRS = parent->TRS * TRS;
	}
}

void Model::Draw() {
	// Se updatea el TRS aca por motivos de optimizacion.
	UpdateTRS();
	rend->updateProgram(TRS);
	
	for ( /*IsOnFrustrum(thisVolume) && */ unsigned int i = 0; i < meshes.size(); i++)
	{
		meshes[i].Draw();
	}
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->Draw();
	}
}

void Model::AddChild(Model* newChild)
{
	children.push_back(newChild);
}

void Model::setPosition(vec3 newPosition) {

	posVec = newPosition;
	translateMat = translate(mat4(1.0f), posVec);
}

void Model::setRotation(vec3 newRot) 
{
	vec3 rot;
	if (newRot.x != rotVec.x)
	{
		rotVec.x = newRot.x;
		rot = vec3(1.0f, 0.0f, 0.0f);
		rotateXMat = rotate(mat4(1.0f), glm::radians(newRot.x), rot);
	}

	if (newRot.y != rotVec.y)
	{
		rotVec.y = newRot.y;
		rot = vec3(0.0f, 1.0f, 0.0f);
		rotateYMat = rotate(mat4(1.0f), glm::radians(newRot.y), rot);
	}

	if (newRot.z != rotVec.z)
	{
		rotVec.z = newRot.z;
		rot = vec3(0.0f, 0.0f, 1.0f);
		rotateZMat = rotate(mat4(1.0f), glm::radians(newRot.z), rot);
	}
}

void Model::setScale(vec3 newScale)
{
	scaleVec = newScale;
	scaleMat = scale(mat4(1.0f), scaleVec);
}