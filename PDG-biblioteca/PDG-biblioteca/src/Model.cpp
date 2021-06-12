#include "Model.h"

Model::Model(string const& path, Renderer* rend)
{
	loadModel(path,rend);
}

// draws the model, and thus all its meshes
void Model::Draw(Renderer* rend)
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].drawMesh(rend);
    }
}
void Model::loadModel(string const& path, Renderer* rend)
{
    // read file via ASSIMP
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
    // check for errors
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }
    // retrieve the directory path of the filepath
    directory = path.substr(0, path.find_last_of('/'));

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene, rend);
}

// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
void Model::processNode(aiNode* node, const aiScene* scene,Renderer* rend)
{
    // process each mesh located at the current node
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene. 
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene, rend));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, rend);
    }

}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene,Renderer* rend)
{
    // data to fill
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<meshTexture> textures;

    // walk through each of the mesh's vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.Normal = vector;
        }
        // texture coordinates
        if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN

    // 1. diffuse maps
    vector<meshTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    vector<meshTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<meshTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<meshTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    return Mesh(vertices, indices, textures,rend);
}

vector<meshTexture> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName)
{
    vector<meshTexture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if (!skip)
        {   // if texture hasn't been loaded already, load it
            meshTexture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char* path, const string& directory)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

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
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}
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
