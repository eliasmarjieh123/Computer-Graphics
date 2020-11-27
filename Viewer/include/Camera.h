#pragma once
#include <glm/glm.hpp>
#include "MeshModel.h"
class Camera:public MeshModel{
public:
	Camera();
	Camera(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name, float ascpectRatio);
	virtual ~Camera();

	void SetCameraLookAt(const glm::vec3& eye, const glm::vec3& at, const glm::vec3& up);
	void UpdateProjectionMatrix();
	const glm::mat4x4& GetProjectionTransformation() const;
	const glm::mat4x4 GetViewTransformation() const;
	void  SetOrthographicProjection( float height, const float aspectRatio, const float zNear, const float zFar);
	void  SetPerspectiveProjection(const float fovy, const float aspectRatio, const float zNear, const float zFar);
	glm::vec3 Camera::GetEye() const;
	glm::vec3 Camera::GetAt() const;
	glm::vec3 Camera::GetUp() const;
	void Camera::UpdateWorldTransformation(glm::vec3 difference);
	void RotateCam(char* lw, int axis, float angle);
	void CamTranslateVertices(char* lw, float x, float y, float z);
	void CamScaleVertices(char* lw, float x, float y, float z);
	void Camera::CameraTransformation_();
	void SetWidth(float w);
	glm::mat4x4 Camera::GetCameraLookAt();
	glm::mat4x4 Camera::GetWorldTransformation();
	void SetIfOrthographicProjection(bool f);
	bool GetIfOrthographicProjection();
	void SetFOV(float FOV);
	void SetEye(glm::vec3 e);
	void SetAt(glm::vec3 a);
	void SetUp(glm::vec3 u);

private:
	glm::mat4x4 CamtWorldMatrix;
	glm::mat4x4 CamrWorldMatrix;
	glm::mat4x4 CamsWorldMatrix;
	glm::mat4x4 CamtLocalMatrix;
	glm::mat4x4 CamrLocalMatrix;
	glm::mat4x4 CamsLocalMatrix;
	glm::mat4x4 CameraTransformation;
	glm::mat4x4 projection_transformation_;
	glm::mat4x4 orthographic_transformation_;
	glm::mat4x4 perspective_transformation_;
	glm::mat4x4 lastLookAtMat_;
	glm::mat4x4 LookAtMat_;
	glm::vec3 eye_;
	glm::vec3 at_;
	glm::vec3 up_;
	glm::vec3 startingEye_;
	glm::vec3 startingAt_;
	glm::vec3 startingUp_;
	glm::vec4 cameraPosition;
	bool isOrthographic_;
	float startingRight_;
	float startingLeft_;
	float startingTop_;
	float startingBottom_;
	float startingNear_;
	float startingFar_;
	float right_;
	float left_;
	float top_;
	float bottom_;
	float width;
	float near_;
	float far_;
	float fovy_;
	float zooming_;
	bool isUsed_;
	float aspectRatio_;
	float height_;
	glm::vec3 lastEye;
};
