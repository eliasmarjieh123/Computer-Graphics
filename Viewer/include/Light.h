#pragma once
#include <glm/glm.hpp>
#include <string>
#include "ShaderProgram.h"

struct Vertex1
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};
class Light
{
	
public:
	Light();
	GLuint GetVao();
	GLuint GetVbo();
	void SetAmbientColor(glm::vec3 color);
	void SetDiffuseColor(glm::vec3 color);
	void SetSpecularColor(glm::vec3 color);
	glm::vec3 GetAmbientColor();
	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();
	glm::mat4x4 GetTransformation();
	void Transform();
	void Rotate(float angle, bool lw, int axis);
	void Translate(bool lw, float x, float y, float z);
	void SetPosition(glm::vec3 p);
	glm::vec3 GetPosition();
	void ActivateLight(bool f);
	bool IsActive();
	int GetAlpha();
	void SetAlpha(int a);
	bool GetIfPoint();
	void SetPointParallel(int f);
	float GetXTranslation();
	float GetYTranslation();
	float GetZTranslation();
	float GetXRotation();
	float GetYRotation();
	float GetZRotation();
	int   GetPP();
	void Light::SetDirection(glm::vec3 d);
	glm::vec3 Light::GetDirection();
private:
	glm::vec3 parallelLights = glm::vec3(0.05f, 0.f, 0.f);
	glm::vec3 AmbientColor;
	glm::vec3 DiffuseColor;
	glm::vec3 SpecularColor;
	glm::vec3 position;
	glm::vec3 Direction;
	glm::mat4x4 LocalXrotation;
	glm::mat4x4 LocalZrotation;
	glm::mat4x4 LocalYrotation;
	glm::mat4x4 WorldXrotation;
	glm::mat4x4 WorldZrotation;
	glm::mat4x4 WorldYrotation;
	glm::mat4x4 WorldTranslate;
	glm::mat4x4 LocalTranslate;
	glm::mat4x4 Transformation;
	float xTranslation;
	float yTranslation;
	float zTranslation;
	float xRotation;
	float yRotation;
	float zRotation;
	bool Active;
	int alphaSpecular;
	int PointParallel;
	GLuint LightVao;
	GLuint LightVbo;
};

