#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"

class MeshModel
{
public:
	MeshModel();
	MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name);
	virtual ~MeshModel();
	const Face& GetFace(int index) const;
	int GetFacesCount() const;
	int GetNormalsCount() const;
	const std::string& GetModelName() const;
	void printFacesAndVertices() const;
	void TranslateAndScaleVertices();
	void RotateModel(char* lw ,int axis, float angle);
	void Transform();
	void ResetModel();
	void TranslateVertices(char* lw, float x, float y, float z);
	void CalculateFacesNormals();
	void ScaleVertices(char* lw, float x, float y, float z);
	glm::vec3 MeshModel::GetVertex(int index)const;
	glm::vec3 MeshModel::GetNormal(int index)const;
	void TranslateAndScaleNormals();
	void CalculateBoundingBox();
	void CalculateCenters();
	glm::vec3 GetVOfBoundingBox(int i);
	glm::vec3 MeshModel::GetCenter(int i)const;
	glm::vec3 MeshModel::GetVertexNormal(int index)const;
	int GetVerticesCount()const;
	void Set_ShowFaceNormals(bool flag);
	void Set_ShowVertexNormals(bool flag);
	void Set_ShowBoundingBox(bool flag);
	bool Get_ShowFaceNormals()const;
	bool Get_ShowVertexNormals()const;
	bool Get_ShowBoundingBox()const;
	void Set_ShowFaceNormalsColor(glm::vec3 Color);
	void Set_ShowVertexNormalsColor(glm::vec3 Color);
	void Set_ShowBoundingBoxColor(glm::vec3 Color);
	glm::vec3 Get_ShowFaceNormalsColor()const;
	glm::vec3 Get_ShowVertexNormalsColor()const;
	glm::vec3 Get_ShowBoundingBoxColor()const;
	void SetWorldTransform(glm::mat4x4 t, glm::mat4x4 s);
	std::vector<Face>  GetFaces();
	std::vector<glm::vec3> GetVertices();
	std::vector<glm::vec3> GetNormals();
	glm::mat4x4 MeshModel::GetTransformation();
	glm::vec3 MeshModel::GetTransformedVertex(int index)const;
protected:
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec3> Facesnormals_;
	std::vector<glm::vec3> BoundingBox;
	std::vector<glm::vec3> Transformedvertices_;
	std::vector<glm::vec3> Transformednormals_;
	std::vector<glm::vec3> Centers;
	glm::mat4x4 tWorldMatrix;
	glm::mat4x4 rXWorldMatrix;
	glm::mat4x4 rYWorldMatrix;
	glm::mat4x4 rWorldMatrix;
	glm::mat4x4 rZWorldMatrix;
	glm::mat4x4 sWorldMatrix;
	glm::mat4x4 tLocalMatrix;
	glm::mat4x4 rXLocalMatrix;
	glm::mat4x4 rYLocalMatrix;
	glm::mat4x4 rZLocalMatrix;
	glm::mat4x4 rLocalMatrix;
	glm::mat4x4 sLocalMatrix;
	glm::mat4x4 Transformation;
	glm::mat4x4 LocalTransformation;
	glm::mat4x4 WorldTransformation;
	std::string model_name_;
	float minX=0;
	float minY=0;
	float minZ=0;
	float maxX=0;
	float maxY=0;
	float maxZ=0;
	bool ShowVertexNormals;
	bool ShowFaceNormals;
	bool ShowBoundingBox;
	glm::vec3 ShowVertexNormalsColor;
	glm::vec3 ShowFaceNormalsColor;
	glm::vec3 ShowBoundingBoxColor;
};
