#include "Light.h"
#include <glm\gtx\transform.hpp>


Light::Light() {
	AmbientColor = glm::vec3(1.f, 1.f, 1.f);
	DiffuseColor = glm::vec3(1.f, 1.f, 1.f);    
	position = glm::vec3(100, 0, 0);
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
}

float Light::GetXTranslation() { return xTranslation; }
float Light::GetYTranslation() { return yTranslation; }
float Light::GetZTranslation() { return zTranslation; }
float Light::GetXRotation() { return xRotation; }
float Light::GetYRotation() { return yRotation; }
float Light::GetZRotation() { return zRotation; }
int Light::GetPP() { return PointParallel; }