#include "Camera.h"
#include <stdio.h>
#include <iostream>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>



Camera::Camera(std::vector<Face> faces, std::vector<glm::vec2> textureCoords,std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name, float ascpectRatio) :MeshModel(faces,textureCoords, vertices, normals, model_name)
{
	right_ = 100;
	left_ = -100;
	top_ = 100;
	bottom_ = -100;
	near_ = 1.f;// 100;//100;
	far_ =2000.f;// -100;//-100;
	fovy_ = glm::radians(70.0f);
	startingRight_ = 100;
	startingLeft_ = -100;
	startingTop_ = 100;
	startingBottom_ = -100;
	startingNear_ = 0.1;//100;
	startingFar_ = 200;// -100;
	aspectRatio_ = 1.77777f;
	isOrthographic_ = true;
	isUsed_ = false;
	eye_ = glm::vec3(0, 0, 10);
	at_ = glm::vec3(0, 0, 0);
	up_ = glm::vec3(0, 1, 0);
	startingEye_ = glm::vec3(0, 0, 100);
	startingAt_ = glm::vec3(0, 0, 0);
	startingUp_ = glm::vec3(0, 1, 0);
	LookAtMat_=CamrLocalMatrix=CamtLocalMatrix=CamsLocalMatrix=CamrWorldMatrix=CamtWorldMatrix=CamsWorldMatrix= CameraTransformation = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	//SetWorldTransform(glm::mat4x4(1,0,0,0,0,1,0,0,0,0,1,0,eye_.x, eye_.y, eye_.z,1) ,glm::mat4x4(1,0,0,0, 0,1,0,0, 0,0,1,0,0,0,0,1));
	lastEye = eye_;
	zooming_ = 1;
	width = 20.000f;
	height_ = width / ascpectRatio;
	projection_transformation_ = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	CamrLocalMatrixX=CamrLocalMatrixY=CamrLocalMatrixZ=CamrWorldMatrixX=CamrWorldMatrixY=CamrWorldMatrixZ= glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	UpdateProjectionMatrix();
	SetCameraLookAt(eye_,at_,up_);
}

Camera::~Camera()
{
	
}

const glm::mat4x4 Camera::GetViewTransformation() const
{
	return LookAtMat_*glm::inverse(CameraTransformation);
}

void Camera::SetOrthographicProjection( float height,const float aspectRatio,const float zNear,const float zFar)
{
	isOrthographic_ = true;
	height_=height =  width/ aspectRatio_;
	projection_transformation_ = glm::ortho(-width/2 , width/2 , -height/2 , height/2 , zNear, zFar);
}

void Camera::SetPerspectiveProjection(const float fovy,const float aspectRatio,const float zNear,const float zFar)
{
	isOrthographic_ = false;
	projection_transformation_ = glm::perspective(fovy, aspectRatio, zNear, zFar);
}

void Camera::UpdateProjectionMatrix()
{
	if (isOrthographic_)
	{
		SetOrthographicProjection(height_, aspectRatio_, near_, far_);
	}
	else
	{
		SetPerspectiveProjection(fovy_, aspectRatio_, near_, far_);
	}
}

void Camera::SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up) {
	LookAtMat_=glm::lookAt(eye, at, up);
}

glm::vec3 Camera::GetEye() const{
	return eye_;
}

glm::vec3 Camera::GetAt() const {
	return at_;
}

glm::vec3 Camera::GetUp() const {
	return up_;
}

const glm::mat4x4& Camera::GetProjectionTransformation() const
{
	return projection_transformation_;
}

void Camera::RotateCam(char* lw, int axis, float angle) {
	glm::mat4x4 mat;
	if (axis == 2) {
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1));
	}
	else if (axis == 1) {
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0));
	}
	else {
		mat = glm::rotate(glm::radians(angle), glm::vec3(1, 0, 0));
	}
	if (strcmp(lw, "local") == 0) {
		CamrLocalMatrix = mat * CamrLocalMatrix;
	}
	else {
		CamrWorldMatrix = mat * CamrWorldMatrix;
	}

}

void Camera::CamTranslateVertices(char* lw, float x, float y, float z) {
	if (strcmp(lw, "world") == 0) {
		CamtWorldMatrix = glm::translate(glm::vec3(x, y, z));
	}
	else {
		CamtLocalMatrix = glm::translate(glm::vec3(x, y, z));
	}
	Transform();
}

void Camera::CamScaleVertices(char* lw, float x, float y, float z) {
	if (strcmp(lw, "world") == 0) {
		CamsWorldMatrix = glm::scale(glm::vec3(x, y, z));
	}
	else {
		CamsLocalMatrix = glm::scale(glm::vec3(x, y, z));
	}
	Transform();
}

void Camera::CameraTransformation_() {
	CamrLocalMatrix = CamrLocalMatrixX * CamrLocalMatrixY * CamrLocalMatrixZ;
	CamrWorldMatrix = CamrWorldMatrixX * CamrWorldMatrixY * CamrWorldMatrixZ;
	CameraTransformation = CamsWorldMatrix * CamrWorldMatrix * CamtWorldMatrix * CamsLocalMatrix * CamtLocalMatrix * CamrLocalMatrix;
}

void Camera::SetWidth(float w) {
	width = w;
}

glm::mat4x4 Camera::GetCameraLookAt() {
	return LookAtMat_;
}

glm::mat4x4 Camera::GetWorldTransformation() {
	return WorldTransformation;
}

void Camera::SetIfOrthographicProjection(bool f) {
	isOrthographic_ = f;
}

bool Camera::GetIfOrthographicProjection() {
	return isOrthographic_;
}

void Camera::SetFOV(float FOV) {
	fovy_ = glm::radians(FOV);
}

void Camera::SetEye(glm::vec3 e)  {
	eye_=e;
}

void Camera::SetAt(glm::vec3 a)  {
	 at_=a;
}

void Camera::SetUp(glm::vec3 u)  {
	up_=u;
}

void Camera::RotateCamera(char* lw, int axis, float angle) {
	glm::mat4x4 mat;
	if (axis == 2) {
		//mat = { {cos(glm::radians(angle)),-sin(glm::radians(angle)),0,0},{sin(glm::radians(angle)),cos(glm::radians(angle)),0,0},{0,0,1,0},{0,0,0,1} };
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1));
		if (strcmp(lw, "local") == 0) {
			CamrLocalMatrixZ = mat;
		}
		else {
			CamrWorldMatrixZ = mat;
		}
	}
	else if (axis == 1) {
		//mat = { {cos(glm::radians(angle)),0,-sin(glm::radians(angle)),0},{0,1,0,0} ,{sin(glm::radians(angle)),0,cos(glm::radians(angle)),0},{0,0,0,1} };
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0));
		if (strcmp(lw, "local") == 0) {
			CamrLocalMatrixY = mat;
		}
		else {
			CamrWorldMatrixY = mat;
		}
	}
	else {
		// mat = { {1,0,0,0}, {0,cos(glm::radians(angle)),-sin(glm::radians(angle)),0},{0,sin(glm::radians(angle)),cos(glm::radians(angle)),0},{0,0,0,1} };
		mat = glm::rotate(glm::radians(angle), glm::vec3(1, 0, 0));
		if (strcmp(lw, "local") == 0) {
			CamrLocalMatrixX = mat;
		}
		else {
			CamrWorldMatrixX = mat;
		}
	}
	CameraTransformation_();

}

void Camera::TranslateCamera(char* lw, float x, float y, float z) {
	if (strcmp(lw, "world") == 0) {
		CamtWorldMatrix = glm::translate(glm::vec3(x, y, z));
	}
	else {
		CamtLocalMatrix = glm::translate(glm::vec3(x, y, z));
	}
	CameraTransformation_();
}

void Camera::ScaleCamera(char* lw, float x, float y, float z) {
	if (strcmp(lw, "world") == 0) {
		CamsWorldMatrix = glm::scale(glm::vec3(x, y, z));
	}
	else {
		CamsLocalMatrix = glm::scale(glm::vec3(x, y, z));
	}
	CameraTransformation_();
}

void Camera::ResetCamera() {
	right_ = 100;
	left_ = -100;
	top_ = 100;
	bottom_ = -100;
	near_ = 1.f;// 100;//100;
	far_ = 2000.f;// -100;//-100;
	fovy_ = glm::radians(70.0f);
	startingRight_ = 100;
	startingLeft_ = -100;
	startingTop_ = 100;
	startingBottom_ = -100;
	startingNear_ = 0.1;//100;
	startingFar_ = 200;// -100;
	aspectRatio_ = 1.77777f;
	isOrthographic_ = true;
	isUsed_ = false;
	eye_ = glm::vec3(0, 0, 10);
	at_ = glm::vec3(0, 0, 0);
	up_ = glm::vec3(0, 1, 0);
	startingEye_ = glm::vec3(0, 0, 100);
	startingAt_ = glm::vec3(0, 0, 0);
	startingUp_ = glm::vec3(0, 1, 0);
	LookAtMat_ = CamrLocalMatrix = CamtLocalMatrix = CamsLocalMatrix = CamrWorldMatrix = CamtWorldMatrix = CamsWorldMatrix = CameraTransformation = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	SetWorldTransform(glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, eye_.x, eye_.y, eye_.z, 1), glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1));
	lastEye = eye_;
	zooming_ = 1;
	width = 20.000f;
	projection_transformation_ = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	CamrLocalMatrixX = CamrLocalMatrixY = CamrLocalMatrixZ = CamrWorldMatrixX = CamrWorldMatrixY = CamrWorldMatrixZ = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	UpdateProjectionMatrix();
	SetCameraLookAt(eye_, at_, up_);
}