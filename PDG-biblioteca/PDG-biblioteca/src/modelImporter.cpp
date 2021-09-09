#include "modelImporter.h"

mat4 ConvertMatrixToGLMFormat(aiMatrix4x4 from);

Model* modelImporter::loadModel(string const& path, bool flipUVs, Renderer* rend)
{
	models_Loaded.push_back(new Model(rend,false));
	stbi_set_flip_vertically_on_load(flipUVs);
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
		return NULL;
	}
	directory = path.substr(0, path.find_last_of('/'));

	models_Loaded.back()->name = scene->mRootNode->mName.C_Str();
	processNode(scene->mRootNode, models_Loaded.back(), models_Loaded.back()->getTRS(), scene, rend);

	Model* newModel = models_Loaded.back();
	models_Loaded.pop_back();
	return newModel;
}

void modelImporter::processNode(aiNode* node, Model* targetParent, mat4 accTransform , const aiScene* scene, Renderer* rend)
{
	Model* parent;
	mat4 transform;


	if (node->mParent == NULL)
	{
		parent = targetParent;
		transform = ConvertMatrixToGLMFormat(node->mTransformation) * accTransform;
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			targetParent->meshes.push_back(processMesh(mesh, scene));
		}
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			cout << "Processing child" << i << " of parent " << parent->name << endl;
			processNode(node->mChildren[i], parent, transform, scene, rend);
		}
	}
	else
	{
		Model* newModel = new Model(rend, false);
		newModel->name = node->mName.C_Str();
		targetParent->AddChild(newModel);
		newModel->parent = targetParent;
		//Copy Meshes
		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
			cout << "Loading mesh " << i << " of node " << node->mName.C_Str() << " into " << newModel->name << endl;
			newModel->meshes.push_back(processMesh(mesh, scene));
		}

		//cout << "Parent is " << parent->name << endl;
		parent = newModel;
		cout << "Parent changed to " << parent->name << endl;

		transform = mat4(0.0f);
		transform[0][0] = 1.0f;
		transform[1][1] = 1.0f;
		transform[2][2] = 1.0f;
		transform[3][3] = 1.0f;
		
		cout << "Node " << parent->name << " processed." << endl;
		cout << "Processing children of " << parent->name << "." << endl;
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			cout << "Processing child" << i << " of parent " << parent->name << endl;
			processNode(node->mChildren[i], parent, transform, scene, rend);
		}
	}
}

Mesh modelImporter::processMesh(aiMesh* mesh, const aiScene* scene)
{
	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<meshTexture> textures;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;

		if (mesh->HasNormals())
		{
			vector.x = mesh->mNormals[i].x;
			vector.y = mesh->mNormals[i].y;
			vector.z = mesh->mNormals[i].z;
			vertex.Normal = vector;
		}
		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;

			vector.x = mesh->mTangents[i].x;
			vector.y = mesh->mTangents[i].y;
			vector.z = mesh->mTangents[i].z;
			vertex.Tangent = vector;

			vector.x = mesh->mBitangents[i].x;
			vector.y = mesh->mBitangents[i].y;
			vector.z = mesh->mBitangents[i].z;
			vertex.Bitangent = vector;
		}
		else
		{
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	vector<meshTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

	vector<meshTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	if (specularMaps.empty()) models_Loaded.back()->hasSpecularMaps = false;
	else models_Loaded.back()->hasSpecularMaps = true;

	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());

	// NORMAL USES HEIGHT INSTEAD OF NORMALS
	vector<meshTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());

	// HEIGHT USES AMBIENT INSTEAD OF HEIGHT 
	vector<meshTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	return Mesh(vertices, indices, textures, models_Loaded.back()->hasSpecularMaps, models_Loaded.back()->_rend);
}

vector<meshTexture> modelImporter::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
	vector<meshTexture> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
	{
		aiString str;
		mat->GetTexture(type, i, &str);
		cout << str.C_Str() << endl;
		bool skip = false;
		for (unsigned int j = 0; j < models_Loaded.back()->textures_loaded.size(); j++)
		{
			if (std::strcmp(models_Loaded.back()->textures_loaded[j].path.data(), str.C_Str()) == 0)
			{
				textures.push_back(models_Loaded.back()->textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip)
		{
			meshTexture texture;
			texture.id = TextureFromFile(str.C_Str(), this->directory, false);
			texture.type = typeName;
			texture.path = str.C_Str();
			textures.push_back(texture);
			models_Loaded.back()->textures_loaded.push_back(texture);
		}
	}
	return textures;
}

unsigned int TextureFromFile(const char* path, const string& directory, bool gamma)
{
	string filename = string(path);
	filename = directory + '/' + filename;

	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width;
	int height;
	int nrComponents;

	unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum format;
		if (nrComponents == 1)
		{
			format = GL_RED;
		}
		else if (nrComponents == 3)
		{
			format = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			format = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		cout << "Texture failed to load at path: " << path << endl;
		stbi_image_free(data);
	}
	return textureID;
}

modelImporter::~modelImporter() {
	models_Loaded.clear();
}

glm::mat4 ConvertMatrixToGLMFormat(aiMatrix4x4 from)
{
	glm::mat4 to;
	//the a,b,c,d in assimp is the row ; the 1,2,3,4 is the column
	to[0][0] = from.a1; to[1][0] = from.a2; to[2][0] = from.a3; to[3][0] = from.a4;
	to[0][1] = from.b1; to[1][1] = from.b2; to[2][1] = from.b3; to[3][1] = from.b4;
	to[0][2] = from.c1; to[1][2] = from.c2; to[2][2] = from.c3; to[3][2] = from.c4;
	to[0][3] = from.d1; to[1][3] = from.d2; to[2][3] = from.d3; to[3][3] = from.d4;
	return to;
}