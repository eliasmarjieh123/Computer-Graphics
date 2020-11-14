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
	void MulMat(char* lw, float TranslateMatrix[4][4]);
	void TranslateAndScaleVertices();
	void RotateModel(char* lw ,int axis, float angle);
	void Transform();
	void ResetModel();
	void TranslateVertices(char* lw, float x, float y, float z);
	void ScaleVertices(char* lw, float x, float y, float z);
	glm::vec3 MeshModel::GetVertex(int index)const;
private:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	    float tWorldMatrix[4][4];
		float rWorldMatrix[4][4];
		float sWorldMatrix[4][4];
		float tLocalMatrix[4][4];
		float rLocalMatrix[4][4];
		float sLocalMatrix[4][4];
		float Transformation[4][4];
	std::vector<glm::vec3> Transformedvertices_;
	std::string model_name_;
};
