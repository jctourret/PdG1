#include "Renderer.h"
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

using namespace std;
using namespace glm;

const GLchar* vertexSource = R"glsl(
#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoor;
layout (location = 2) in vec3 normal;

out vec2 texCoord;
out vec3 fposition;
out vec3 fnormal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;	

void main()
{
gl_Position = Projection * View * Model * vec4(position, 1.0);
fnormal = mat3(Model)*normal;
fposition = vec4(Model*vec4(position,1.0f)).xyz;
texCoord = texCoor;
}
)glsl";

const GLchar* fragmentSource = R"glsl(
#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;    
    float shininess;
}; 

struct Light {
    vec3 position;
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;

	float cutOff;
};

out vec4 outColor;

in vec2 texCoord;
in vec3 fposition;
in vec3 fnormal;

uniform sampler2D tex;
uniform Light light;
uniform Light dirLight;
uniform Light pointLight;
uniform Light spotLight;
uniform Material mat;
uniform vec3 viewPos;

vec3 calculateLight(int lightType);

void main()
{	

vec4 texColor = texture(tex, texCoord);

//vec3 lightResultTest = calculateLight(0);
//vec3 lightResultPoint = calculateLight(1);
//vec3 lightResultDir = calculateLight(2);
vec3 lightResultSpot = calculateLight(3);
vec3 lightResultTotal = /*lightResultTest + lightResultPoint + lightResultDir +*/ lightResultSpot;

//outColor = texColor;
outColor = texColor * vec4(lightResultTotal, 1.0f);
 
}

vec3 calculateLight(int lightType)
{
	
	if(lightType==0) //testLight
	{
		vec3 ambientLight = vec3(1.0f);
		vec3 specular= vec3(1.0f);
		vec3 diffuseFinal= vec3(1.0f);
			
		vec3 posToLightDirVec = normalize(fposition-light.position);

		//Ambient Light
		ambientLight = light.ambient * mat.ambient;
		
		//Diffuse Light
		float diffuse = clamp(dot(posToLightDirVec,fnormal),0,1); // producto punto entre la distancia con la luz y la normal
		diffuseFinal = light.diffuse * (diffuse* mat.diffuse);
		
		// Specular Light
		vec3 viewDir = normalize(viewPos-fposition);
		vec3 reflectDir = reflect(-posToLightDirVec,fnormal);
		float spec = pow(max(dot(viewDir,reflectDir),0.0), mat.shininess);	
		specular = light.specular * (spec * mat.specular);
		
		vec3 lightResult = ambientLight + diffuseFinal + specular;
		
		return lightResult;
	}
	if(lightType==1) //pointLight
	{
		vec3 ambientLight = vec3(1.0f);
		vec3 specular= vec3(1.0f);
		vec3 diffuseFinal= vec3(1.0f);
		
		vec3 posToLightDirVec = normalize(fposition-pointLight.position);

		//Ambient Light
		ambientLight = pointLight.ambient * mat.ambient;
		
		//Diffuse Light
		float diffuse = clamp(dot(posToLightDirVec,fnormal),0,1); // producto punto entre la distancia con la luz y la normal
		diffuseFinal = pointLight.diffuse * (diffuse* mat.diffuse);
		
		//Specular Light	
		vec3 viewDir = normalize(viewPos-fposition);
		vec3 reflectDir = reflect(-posToLightDirVec,fnormal);
		float spec = pow(max(dot(viewDir,reflectDir),0.0), mat.shininess);	
		specular = pointLight.specular * (spec * mat.specular);
		
		//Atenuation
		float distance    = length(pointLight.position - fposition);
		float attenuation = 1.0 / (pointLight.constant + pointLight.linear * distance + pointLight.quadratic * (distance * distance));  
		
		ambientLight *= attenuation;
		diffuseFinal *= attenuation;
		specular *= attenuation;

		vec3 lightResult = ambientLight + diffuseFinal + specular;

		return lightResult;
	}
	if (lightType==2) //dirLight
	{
		vec3 ambientLight = vec3(0.0f);
		vec3 specular= vec3(0.0f);
		vec3 diffuseFinal= vec3(0.0f);

		vec3 posToLightDirVec = normalize(-dirLight.position);
			
		//Ambient Light
		ambientLight = dirLight.ambient * mat.ambient;
		
		//Diffuse Light
		float diffuse = clamp(dot(posToLightDirVec,fnormal),0,1); // producto punto entre la distancia con la luz y la normal
		diffuseFinal = dirLight.diffuse * (diffuse* mat.diffuse);
		
		// Specular Light
		vec3 viewDir = normalize(viewPos-fposition);
		vec3 reflectDir = reflect(-posToLightDirVec,fnormal);
		float spec = pow(max(dot(viewDir,reflectDir),0.0), mat.shininess);	
		specular = dirLight.specular * (spec * mat.specular);
		
		vec3 lightResult = ambientLight + diffuseFinal + specular;

		return lightResult;
	}
	if(lightType==3) //spotLight
	{
		vec3 ambientLight = vec3(0.0f);
		vec3 specular= vec3(0.0f);
		vec3 diffuseFinal= vec3(0.0f);
			
		//Ambient Light
		ambientLight = spotLight.ambient * mat.ambient;
		
		vec3 posToLightDirVec = normalize(fposition-spotLight.position);
		
		float theta = dot(posToLightDirVec, normalize(-spotLight.direction));
		
		if(theta > spotLight.cutOff) 
		{       
			//Diffuse Light
			float diffuse = clamp(dot(posToLightDirVec,fnormal),0,1); // producto punto entre la distancia con la luz y la normal
			diffuseFinal = spotLight.diffuse * (diffuse* mat.diffuse);
			
			// Specular Light	
			vec3 viewDir = normalize(viewPos-fposition);
			vec3 reflectDir = reflect(-posToLightDirVec,fnormal);
			float spec = pow(max(dot(viewDir,reflectDir),0.0), mat.shininess);	
			specular = spotLight.specular * (spec * mat.specular);
		}	
		vec3 lightResult = ambientLight + diffuseFinal + specular;
		return lightResult;
		
	}
	else
	{
		return vec3(0.0f);
	}
}

)glsl";

Renderer::Renderer()
{
	defaultMat = new Material(vec3(1.0f, 0.5f, 0.31f), vec3(1.0f, 0.5f, 0.31f), vec3(0.5f, 0.5f, 0.5f), 32.0f);
}
Renderer::~Renderer()
{
	if (defaultMat) delete defaultMat;
}

void Renderer::initVertexShader() {
	_vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(_vertexShader, 1, &vertexSource, NULL);
	glCompileShader(_vertexShader);

}
void Renderer::initFragmentShader() {
	_fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(_fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(_fragmentShader);
}

void Renderer::initShaderProgram() {
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, _vertexShader);
	glAttachShader(_shaderProgram, _fragmentShader);
	glLinkProgram(_shaderProgram);
	glValidateProgram(_shaderProgram);
	glUseProgram(_shaderProgram);
	setVP();
}

void Renderer::creatoVAO(unsigned int &vao)
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
}

void Renderer::createVBO(float* vertexDataArray, int arraySize, unsigned int &vbo)
{
	int vertexSize = sizeof(vertexDataArray) * arraySize;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, vertexSize, vertexDataArray, GL_STATIC_DRAW);
}

void Renderer::createEBO(int* indexArray, int arraySize, unsigned int &_ebo) 
{
	glGenBuffers(1, &_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexArray) * arraySize, indexArray, GL_STATIC_DRAW);
}

void Renderer::setPosAttrib() 
{
	_posAttrib = glGetAttribLocation(_shaderProgram, "position");
	glVertexAttribPointer(_posAttrib, posElementsAmount, GL_FLOAT, GL_FALSE, attribElementsAmount * sizeof(float), 0);
	glEnableVertexAttribArray(_posAttrib); //cambie esto de 0 a _posAttrib
}

void Renderer::setTextureAttrib()
{
	_textureAttrib = glGetAttribLocation(_shaderProgram, "texCoor");
	glVertexAttribPointer(_textureAttrib, texElementsAmount, GL_FLOAT, GL_FALSE, attribElementsAmount * sizeof(float), (void*) (3 * sizeof(float)));
	glEnableVertexAttribArray(_textureAttrib);//cambie esto de 1 a _textureAttrib
}

void Renderer::setNormalAttrib()
{
	_normalAttrib = glGetAttribLocation(_shaderProgram, "normal");
	glVertexAttribPointer(_normalAttrib, normalElementsAmount, GL_FLOAT, GL_FALSE, attribElementsAmount * sizeof(float), (void*)(5 * sizeof(float)));
	glEnableVertexAttribArray(_normalAttrib);//cambie esto de 1 a _textureAttrib
}

void Renderer::deleteShaderProgram() {
	glDeleteProgram(_shaderProgram);
}

void Renderer::deleteFragmentShader() {
	glDeleteShader(_fragmentShader);
}

void Renderer::deleteVertexShader() {
	glDeleteShader(_vertexShader);
}

void Renderer::drawSprite(glm::mat4x4 trs, unsigned int vbo, unsigned int vao, float* vertex, unsigned int size, unsigned int indexSize)
{
	setMaterial(defaultMat);
	bindSpriteBuffers(vbo,vao,vertex,size);
	setSpriteAttrib();
	startProgram(trs);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
}
void Renderer::drawSprite(glm::mat4x4 trs, unsigned int vbo, unsigned int vao, float* vertex, unsigned int size, unsigned int indexSize, Material* material)
{
	setMaterial(material);
	bindSpriteBuffers(vbo, vao, vertex, size);
	setSpriteAttrib();
	startProgram(trs);
	glDrawElements(GL_TRIANGLES, indexSize, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); //unbind
}

unsigned int Renderer::getShaderProgram()
{
	return _shaderProgram;
}

void Renderer::setTexture(unsigned int texture)
{	
	unsigned int uniformTex = glGetUniformLocation(_shaderProgram, "tex");
	glUseProgram(_shaderProgram);
	glUniform1i(uniformTex, 1);
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::bindSpriteBuffers(unsigned int vbo, unsigned int vao, float* vertex, float size) {
	unsigned int memorySize = sizeof(float) * size;
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, memorySize, vertex, GL_STATIC_DRAW);
}

void Renderer::setSpriteAttrib() {
	glUniform1i((glGetUniformLocation(_shaderProgram, "tex")), 0);// CHECKEAR ESTO
	setPosAttrib();
	setTextureAttrib();
	setNormalAttrib();
}

void Renderer::bindTexture(unsigned int texture) {
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);
}

void Renderer::startProgram(mat4 model) {
	unsigned int transformLocation = glGetUniformLocation( _shaderProgram, "Model");
	glUseProgram(_shaderProgram);
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(model));
}

void Renderer::blendTexture() {
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Renderer::unblendTexture() {
	glDisable(GL_BLEND);
}

void Renderer::setVP(){
	unsigned int projectionLocation = glGetUniformLocation(_shaderProgram, "Projection");
	unsigned int viewLocation = glGetUniformLocation(_shaderProgram, "View");
	mat4 proj = mat4(1.0f);
	mat4 view = mat4(1.0f);
	view = lookAt(vec3(0.0, 0.0f, 1.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	proj = /*glm::ortho(-4.0f,4.0f,-2.0f,2.0f,-100.0f,100.0f); */perspective(45.0f, 2.0f, 0.1f, 100.0f);//el aspect esta mal pero queda bien porque cambie las medidas de los cuadrados
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(proj));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));
}

void Renderer::updateView(vec3 position, vec3 target){
	unsigned int viewLocation = glGetUniformLocation(_shaderProgram, "View");
	mat4 view = lookAt(position, target, vec3(0.0f, 1.0f, 0.0f));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

	unsigned int viewPos = glGetUniformLocation(_shaderProgram, "ViewPos");
	glUniform3fv(viewPos, 1, value_ptr(position));
}

void Renderer::updateView(vec3 position, vec3 front, vec3 up)
{
	unsigned int viewLocation = glGetUniformLocation(_shaderProgram, "View");
	mat4 view;
	view = lookAt(position, position + front, up);
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(view));

	unsigned int viewPos = glGetUniformLocation(_shaderProgram, "ViewPos");
	glUniform3fv(viewPos, 1, value_ptr(position));
}

int Renderer::getAttribElementsAmount()
{
	return attribElementsAmount;
}

void Renderer::setMaterial(Material* material)
{
	unsigned int uniformMatAmb = glGetUniformLocation(_shaderProgram, "mat.ambient");
	unsigned int uniformMatDiff = glGetUniformLocation(_shaderProgram, "mat.diffuse");
	unsigned int uniformMatSpec = glGetUniformLocation(_shaderProgram, "mat.specular");
	unsigned int uniformMatShin = glGetUniformLocation(_shaderProgram, "mat.shininess");
	glUniform3fv(uniformMatAmb, 1, value_ptr(material->_ambient));
	glUniform3fv(uniformMatDiff, 1, value_ptr(material->_diffuse));
	glUniform3fv(uniformMatSpec, 1, value_ptr(material->_specular));
	glUniform1f(uniformMatShin, material->_shininess);
}

void Renderer::updateLight(glm::vec3 position, glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float constant, float linear, float quadratic, float cutOff, unsigned int lightKind)
{

	switch (lightKind)
	{
	default:
	case 0:
		glUniform3fv(glGetUniformLocation(_shaderProgram, "light.position"), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "light.ambient" ), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "light.diffuse" ), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "light.specular" ), 1, value_ptr(specular));
		break;
	case 1:
		glUniform3fv(glGetUniformLocation(_shaderProgram, "pointLight.position"), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "pointLight.ambient"), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "pointLight.diffuse"), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "pointLight.specular"), 1, value_ptr(specular));
		glUniform1f(glGetUniformLocation(_shaderProgram, "pointLight.constant"), constant);// 1.0f
		glUniform1f(glGetUniformLocation(_shaderProgram, "pointLight.linear"), linear);// 0.09f
		glUniform1f(glGetUniformLocation(_shaderProgram, "pointLight.quadratic"), quadratic);// 0.032f
		break;
	case 2:
		glUniform3fv(glGetUniformLocation(_shaderProgram, "dirLight.position"), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "dirLight.ambient"), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "dirLight.diffuse"), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "dirLight.specular"), 1, value_ptr(specular));
		break;
	case 3:
		glUniform3fv(glGetUniformLocation(_shaderProgram, "spotLight.position"), 1, value_ptr(position));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "spotLight.direction"), 1, value_ptr(direction));//vec3(0.0f, 1.0f, 0.0f)
		glUniform3fv(glGetUniformLocation(_shaderProgram, "spotLight.ambient"), 1, value_ptr(ambient));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "spotLight.diffuse"), 1, value_ptr(diffuse));
		glUniform3fv(glGetUniformLocation(_shaderProgram, "spotLight.specular"), 1, value_ptr(specular));
		glUniform1f(glGetUniformLocation(_shaderProgram, "spotLight.cutOff"), glm::cos(cutOff));// glm::radians(12.5f)
		break;
	}

}