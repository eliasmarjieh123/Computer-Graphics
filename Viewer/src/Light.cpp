#include "Light.h"
#include <glm\gtx\transform.hpp>
#include <glad\glad.h>
#include <Texture2D.h>


Light::Light() {
	AmbientColor = glm::vec3(1.f, 1.f, 1.f);
	DiffuseColor = glm::vec3(1.f, 1.f, 1.f);    
	position = glm::vec3(1.f, 1.f, 1.f);
	Direction = glm::vec3(0, 0, 0);
	SpecularColor = glm::vec3(1.f, 1.f, 1.f);
	Active = true;
    Transformation=LocalTranslate=LocalXrotation=LocalYrotation=LocalZrotation=WorldTranslate=WorldXrotation=WorldYrotation=WorldZrotation= glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	alphaSpecular=5;
	PointParallel = 1;
	xTranslation=0;
	yTranslation=0;
	zTranslation=0;
	xRotation=0;
	yRotation=0;
	zRotation=0;
	float point[3] = { position.x,position.y,position.z };
	glGenVertexArrays(1, &LightVao);
	glGenBuffers(1, &LightVbo);
	
	glBindVertexArray(LightVao);
	glBindBuffer(GL_ARRAY_BUFFER, LightVbo);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex1), point, GL_STATIC_DRAW);
	
	// Vertex Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	
	// Normals attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	
	// Vertex Texture Coords
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (GLvoid*)(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);
	
	// unbind to make sure other code does not change it somewhere else
	glBindVertexArray(0);
	glGenVertexArrays(1, &LightVao);
}

void Light::SetAmbientColor(glm::vec3 color) {
    AmbientColor = color;
}

void Light::SetDiffuseColor(glm::vec3 color) {
    DiffuseColor = color;
}

void Light::SetSpecularColor(glm::vec3 color) {
    SpecularColor = color;
}

glm::vec3 Light::GetAmbientColor() {
    return AmbientColor;
}

glm::vec3 Light::GetDiffuseColor() {
    return DiffuseColor;
}

glm::vec3 Light::GetSpecularColor() {
    return SpecularColor;
}

glm::mat4x4 Light::GetTransformation() {
    return Transformation;
}

void Light::Transform() {
    Transformation = WorldXrotation * WorldYrotation * WorldZrotation * WorldTranslate * LocalTranslate * LocalXrotation * LocalYrotation * LocalZrotation;
}

void Light::Rotate(float angle, bool lw, int axis) {
	glm::mat4x4 mat;
	if (axis == 2) {
		zRotation = angle;
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1));
		if (lw == 0) {
			LocalXrotation = mat;
		}
		else {
			WorldXrotation = mat;
		}
	}
	else if (axis == 1) {
		yRotation = angle;
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0));
		if (lw == 0) {
			LocalYrotation = mat;
		}
		else {
			WorldYrotation = mat;
		}
	}
	else {
		xRotation = angle;
		mat = glm::rotate(glm::radians(angle), glm::vec3(1, 0, 0));
		if (lw == 0) {
			LocalZrotation = mat;
		}
		else {
			WorldZrotation = mat;
		}
	}
	Transform();

}

void Light::Translate(bool lw, float x, float y, float z) {
	LocalTranslate = glm::translate(glm::vec3(x, y, z));
	xTranslation = x;
	yTranslation = y;
	zTranslation = z;
	Transform();
}

void Light::SetPosition(glm::vec3 p) {
	position = p;
}

glm::vec3 Light::GetPosition() {
	return position;
}

void Light::ActivateLight(bool f) {
	Active = f;
}

bool Light::IsActive() {
	return Active;
}

int Light::GetAlpha() {
	return alphaSpecular;
}

void Light::SetAlpha(int a) {
	alphaSpecular = a;
}

bool Light::GetIfPoint() {
	return PointParallel;
}

void Light::SetPointParallel(int f) {
	PointParallel = f;
	if (f == 1) {
		float point[3] = { position.x,position.y,position.z };
		glGenVertexArrays(1, &LightVao);
		glGenBuffers(1, &LightVbo);

		glBindVertexArray(LightVao);
		glBindBuffer(GL_ARRAY_BUFFER, LightVbo);
		glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(Vertex1), point, GL_STATIC_DRAW);

		// Vertex Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		// Normals attribute
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (GLvoid*)(3 * sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		// Vertex Texture Coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex1), (GLvoid*)(6 * sizeof(GLfloat)));
		glEnableVertexAttribArray(2);

		// unbind to make sure other code does not change it somewhere else
		glBindVertexArray(0);
		glGenVertexArrays(1, &LightVao);
	}
	else {
		glm::vec3 direction = normalize(Direction);
		direction = 0.014f * direction + parallelLights;
		float point[24] = { parallelLights.x, parallelLights.y, parallelLights.z,direction.x, direction.y, direction.z,
							parallelLights.x + 0.005, parallelLights.y, parallelLights.z,direction.x + 0.005, direction.y, direction.z,
							parallelLights.x + 0.006, parallelLights.y, parallelLights.z,direction.x + 0.006, direction.y, direction.z,
							parallelLights.x + 0.007, parallelLights.y, parallelLights.z,direction.x + 0.007, direction.y, direction.z };
		glGenVertexArrays(1, &LightVao);
		glGenBuffers(1, &LightVbo);
		glBindVertexArray(LightVao);
		glBindBuffer(GL_ARRAY_BUFFER, LightVbo);
		glBufferData(GL_ARRAY_BUFFER, sizeof(point), &point, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
	}
}

float Light::GetXTranslation() { return xTranslation; }
float Light::GetYTranslation() { return yTranslation; }
float Light::GetZTranslation() { return zTranslation; }
float Light::GetXRotation() { return xRotation; }
float Light::GetYRotation() { return yRotation; }
float Light::GetZRotation() { return zRotation; }
int Light::GetPP() { return PointParallel; }

void Light::SetDirection(glm::vec3 d) {
	Direction = d;
}

glm::vec3 Light::GetDirection() {
	return Direction;
}

GLuint Light::GetVao()
{
	return LightVao;
}
GLuint Light::GetVbo()
{
	return LightVbo;
}


