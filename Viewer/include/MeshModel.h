#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"

class MeshModel
{
public:
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	const std::string& GetModelName() const;
	void printFacesAndVertices() const;
	void MulMat(float TranslateMatrix[4][4]);
	void TranslateVertices(int first=1, float x=0, float y=0, float z=0);
	void ScaleVertices(int first = 1, float x = 0, float y = 0, float z = 0);
	void RotateModel(int Sync,int axis, float angle);
	glm::vec3 MeshModel::GetVertex(int index)const;
private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<Face> Originalfaces_;
	std::vector<glm::vec3> Originalvertices_;
	std::vector<glm::vec3> Originalnormals_;
	glm::vec2 lastScale;
	glm::vec2 lastTranslate;
	float latsRotationByX = 0;
	float latsRotationByY = 0;
	float latsRotationByZ = 0;
	std::string model_name_;
};
