//#include "Model.h"
//
//GLint TextureFromFile(const char *path, string directory)
//{
//	string filename = string(path);
//	filename = directory + '/' + filename;
//	GLuint textureID;
//	glGenTextures(1, &textureID);
//
//	int width;
//	int height;
//
//	unsigned char *image = stbi_load(filename.c_str(), &width, &height, 0, STBI_rgb_alpha);
//	glBindTexture(GL_TEXTURE_2D, textureID);
//	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
//	glGenerateMipmap(GL_TEXTURE_2D);
//	
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glBindTexture(GL_TEXTURE_2D, 0);
//
//	stbi_image_free(image);
//
//	return textureID;
//}
//
//
//Model::Model(GLchar * path)
//{
//	loadModel(path);
//}
//
//Model::~Model()
//{
//}
//
//void Model::draw()
//{
//	for (int i = 0; i < meshes.size(); i++)
//	{
//		meshes[i].draw();
//	}
//}
//
//void Model::loadModel(string path)
//{
//	Assimp::Importer importer;
//	const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
//
//	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
//	{
//		cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
//		return;
//	}
//	directory = path.substr(0,path.find_last_of('/'));
//	processNode(scene->mRootNode, scene);
//}
//
//void Model::processNode(aiNode * node, const aiScene * scene)
//{
//	for (GLuint i = 0; i < node->mNumMeshes; i++)
//	{
//		aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
//		meshes.push_back(processMesh(mesh,scene));
//	}
//
//	for (GLuint i = 0; i < node->mNumChildren; i++)
//	{
//		processNode(node->mChildren[i], scene);
//	}
//}
//
//Mesh Model::processMesh(aiMesh * mesh, const aiScene * scene)
//{
//	vector<Vertex> vertices;
//	vector<GLuint> indices;
//	vector<Texture> textures;
//
//	for (GLuint i = 0; i < mesh->mNumVertices; i++)
//	{
//		Vertex vertex;
//		vec3 vector3;
//
//		vector3.x = mesh->mVertices[i].x;
//		vector3.y = mesh->mVertices[i].y;
//		vector3.z = mesh->mVertices[i].z;
//		vertex.position = vector3;
//
//		vector3.x = mesh->mNormals[i].x;
//		vector3.y = mesh->mNormals[i].y;
//		vector3.z = mesh->mNormals[i].z;
//		vertex.normal = vector3;
//
//		if (mesh->mTextureCoords[0])
//		{
//			vec2 vector2;
//
//			vector2.x = mesh->mTextureCoords[0][i].x;
//			vector2.y = mesh->mTextureCoords[0][i].y;
//			
//			vertex.texCoords = vector2;
//		}
//		else
//		{
//			vertex.texCoords = vec2(0.0f);
//		}
//		vertices.push_back(vertex);
//	}
//
//	for (GLuint i = 0; i < mesh->mNumFaces; i++)
//	{
//		aiFace face = mesh->mFaces[i];
//
//		for (GLuint j = 0; j < face.mNumIndices; j++)
//		{
//			indices.push_back(face.mIndices[j]);
//		}
//	}
//
//	if (mesh->mMaterialIndex >= 0)
//	{
//		aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
//		
//		vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
//		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
//
//
//		vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
//		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
//	}
//
//	return Mesh(vertices,indices,textures);
//}
//
//vector<Texture> Model::loadMaterialTextures(aiMaterial * mat, aiTextureType type, string typeName)
//{
//	vector<Texture> textures;
//	for (GLuint i = 0; i < mat->GetTextureCount(type); i++)
//	{
//		aiString str;
//		mat->GetTexture(type, i, &str);
//
//		GLboolean skip = false;
//		for (GLuint j = 0; j < textures_loaded.size(); j++)
//		{
//			if (textures_loaded[j].path == str)
//			{
//				textures.push_back(textures_loaded[j]);
//				skip = true;
//				break;
//			}
//		}
//
//		if (!skip)
//		{
//			Texture texture;
//			texture.id = TextureFromFile(str.C_Str(), directory);
//			texture.type = typeName;
//			texture.path = str;
//			textures.push_back(texture);
//
//			textures_loaded.push_back(texture);
//		}
//	}
//
//	return textures;
//}
//
//
