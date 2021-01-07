#include "Light.h"
#include <glm\gtx\transform.hpp>


Light::Light() {
    AmbientColor = glm::vec3(0, 0, 255);
    DiffuseColor = glm::vec3(0, 0, 255);
    SpecularColor = glm::vec3(0, 0, 255);
    position = glm::vec3(100, 0, 0);
	Active = true;
    Transformation=LocalTranslate=LocalXrotation=LocalYrotation=LocalZrotation=WorldTranslate=WorldXrotation=WorldYrotation=WorldZrotation= glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
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
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1));
		if (lw == 0) {
			LocalXrotation = mat;
		}
		else {
			WorldXrotation = mat;
		}
	}
	else if (axis == 1) {
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0));
		if (lw == 0) {
			LocalYrotation = mat;
		}
		else {
			WorldYrotation = mat;
		}
	}
	else {
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
	position = glm::vec3(x, y, z);
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

