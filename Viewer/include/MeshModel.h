#pragma once
#include <glm/glm.hpp>
#include <string>
#include "Face.h"
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include "MeshModel.h"
#include "Face.h"
#include <Texture2D.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 textureCoords;
};


class MeshModel
{
public:
	const glm::vec3& GetColor() const;
	void MeshModel::SetColor(const glm::vec3& color);
	GLuint GetVAO() const;
	const std::vector<Vertex>& MeshModel::GetModelVertices();
	MeshModel();
	MeshModel(std::vector<Face> faces, std::vector<glm::vec2> textureCoords, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name);
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
	void ScaleVertices(char* lw, float x, float y, float z, float ScaleFactor);
	glm::vec3 MeshModel::GetVertex(int index)const;
	glm::vec3 MeshModel::GetNormal(int index)const;
	void TranslateAndScaleNormals();
	void CalculateBoundingBox();
	void CalculateCenters();
	glm::vec4 GetVOfBoundingBox(int i);
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
	void SetMinX(float x);
	void SetMinY(float y);
	void SetMinZ(float z);
	void SetMaxX(float x);
	void SetMaxY(float y);
	void SetMaxZ(float z);
	void SetMinW(float w);
	void SetMaxW(float w);
	float MeshModel::GetMinX();
	float MeshModel::GetMinY();
	float MeshModel::GetMinZ();
	float MeshModel::GetMaxX();
	float MeshModel::GetMaxY();
	float MeshModel::GetMaxZ();
	float MeshModel::GetMinW();
	float MeshModel::GetMaxW();
	void ScaleModel(float scale);
	glm::mat4x4 MeshModel::GetModelScale();
	glm::vec3 MeshModel::GetFaceColor(int i);
	void ActivateGrayScale(bool flag);
	bool GetIfGrayScale();
	void ActivateZbufferAlgo(bool flag);
	bool GetIfZbufferAlgo();
	void SetAmbientColor(glm::vec3 color);
	void SetDiffuseColor(glm::vec3 color);
	void SetSpecularColor(glm::vec3 color);
	glm::vec3 GetAmbientColor();
	glm::vec3 GetDiffuseColor();
	glm::vec3 GetSpecularColor();
	glm::vec3 MeshModel::GetModelColor();
	void SetShadingType(int st);
	int  GetShadingType();
	glm::mat4x4 GetRotation();
	glm::mat4x4 MeshModel::GetWorldTransformation();
	glm::mat4x4 MeshModel::GetModelTransformation();
	float MeshModel::GetXRotationAngleLocal() ;
	float MeshModel::GetYRotationAngleLocal() ;
	float MeshModel::GetZRotationAngleLocal() ;
	float MeshModel::GetZRotationAngleWorld() ;
	float MeshModel::GetYRotationAngleWorld() ;
	float MeshModel::GetXRotationAngleWorld() ;
	float MeshModel::GetXTranslateLocal() ;
	float MeshModel::GetYTranslateLocal() ;
	float MeshModel::GetZTranslateLocal() ;
	float MeshModel::GetZTranslateWorld() ;
	float MeshModel::GetYTranslateWorld() ;
	float MeshModel::GetXTranslateWorld() ;
	float MeshModel::GetXScaleLocal();
	float MeshModel::GetYScaleLocal();
	float MeshModel::GetZScaleLocal();
	float MeshModel::GetZScaleWorld();
	float MeshModel::GetYScaleWorld();
	float MeshModel::GetXScaleWorld();
	float MeshModel::GetScaleFactor();
	int MeshModel::GetMethod();
	void MeshModel::SetMethod(int m);
	bool MeshModel::GetIfThereIsVT();

protected:
	int Method;
	std::vector<glm::vec3> textureCoords;
	std::vector<Vertex> modelVertices;
	GLuint vbo;
	GLuint vao;
	int ShadingType;
	float ScaleFactor;
	glm::vec3 AmbientColor;
	glm::vec3 DiffuseColor;
	glm::vec3 SpecularColor;
	std::vector<Face> faces_;
	std::vector<glm::vec3> vertices_;
	std::vector<glm::vec3> normals_;
	std::vector<glm::vec2> textureCoords_;
	std::vector<glm::vec3> Facesnormals_;
	std::vector<glm::vec4> BoundingBox;
	std::vector<glm::vec3> Transformedvertices_;
	std::vector<glm::vec3> Transformednormals_;
	std::vector<glm::vec3> Centers;
	std::vector<glm::vec3> FacesColors;
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
	glm::mat4x4 ModelScale;
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
	float minW=0;
	float maxW=0;
	bool ShowVertexNormals;
	bool ShowFaceNormals;
	bool ShowBoundingBox;
	glm::vec3 ShowVertexNormalsColor;
	glm::vec3 ShowFaceNormalsColor;
	glm::vec3 ShowBoundingBoxColor;
	bool GrayScale;
	bool ZbufferAlgo;
	glm::vec3 color;
   
	float AngleX;
	float AngleY;
	float AngleZ;
	float WAngleX;
	float WAngleY;
	float WAngleZ;
	float TranslateX;
	float TranslateY;
	float TranslateZ;
	float WTranslateX;
	float WTranslateY;
	float WTranslateZ;
	float ScaleX;
	float ScaleY;
	float ScaleZ;
	float WScaleX;
	float WScaleY;
	float WScaleZ;
	bool VT;
};
