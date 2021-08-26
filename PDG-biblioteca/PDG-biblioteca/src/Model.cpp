#include "Model.h"
#define STB_IMAGE_IMPLEMENTATION

Model::Model(Renderer* rend, bool gamma) : gammaCorrection(gamma), Entity(rend)
{
	_rend = rend;
}
void Model::Draw() {
	rend->updateProgram(TRS);
	for (unsigned int i = 0; i < meshes.size(); i++)
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

	UpdateTRS();
}