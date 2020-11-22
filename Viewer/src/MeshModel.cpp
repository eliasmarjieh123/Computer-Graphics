#include "MeshModel.h"
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals)
{
	tLocalMatrix = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	sLocalMatrix = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	rLocalMatrix = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	tWorldMatrix = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	sWorldMatrix = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	rWorldMatrix = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
	Transformation = glm::mat4x4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}

MeshModel::~MeshModel()
{
}

const Face& MeshModel::GetFace(int index) const
{
	return faces_[index];
}

int MeshModel::GetFacesCount() const
{
	return faces_.size();
}

int MeshModel::GetNormalsCount() const
{
	return normals_.size();
}

const std::string& MeshModel::GetModelName() const
{
	return model_name_;
}

void MeshModel::printFacesAndVertices() const
{
	int i = 0;
	std::cout << "Printing faces..." << std::endl;
	while (i < this->GetFacesCount()) {
		const Face& face = this->GetFace(i);
		int j = 0;
		while (j < 3) {
			std::cout << face.GetVertexIndex(j);
			std::cout << "  ";
			std::cout << face.GetNormalIndex(j);
			std::cout << "  ";
			std::cout << face.GetTextureIndex(j);
			std::cout << std::endl;
			j++;
		}
		i++;
	}
	i = 0;
	std::cout <<std::endl<< "Printing vertices..." << std::endl;
	while (i < vertices_.size()) {
		std::cout << vertices_[i][0];
		std::cout << "  ";
		std::cout << vertices_[i][1];
		std::cout << "  ";
		std::cout << vertices_[i][2];
		std::cout << std::endl;
		i++;
	}
}

void MeshModel::CalculateFacesNormals() {
	Facesnormals_.clear();
	for (int i = 0; i < this->GetFacesCount(); i++) {
		int p1 = this->GetFace(i).GetVertexIndex(0);
		int p2 = this->GetFace(i).GetVertexIndex(1);
		int p3 = this->GetFace(i).GetVertexIndex(2);
		glm::vec3 v1 = this->GetVertex(p1 - 1), v2 = this->GetVertex(p2 - 1), v3 = this->GetVertex(p3 - 1);
		glm::vec3 n =glm::normalize(glm::cross(glm::vec3(v2-v1),glm::vec3(v3-v1)));
		glm::vec4 v(n.x, n.y, n.z, 1);
		v = glm::scale(glm::vec3(40, 40, 40)) * v;
		n.x = v.x / v.w;
		n.y = v.y / v.w;
		n.z = v.z / v.w;
		n =n+ this->GetCenter(i);
		Facesnormals_.push_back(n);
	}
}

void MeshModel::TranslateAndScaleNormals() {
	Transformednormals_ = normals_;
	for (int i = 0; i < this->GetFacesCount(); i++) {
		Face face = this->GetFace(i);
		int vi1 = face.GetVertexIndex(0);
		int vi2 = face.GetVertexIndex(1);
		int vi3 = face.GetVertexIndex(2);
		int vni1 = face.GetNormalIndex(0);
		int vni2 = face.GetNormalIndex(1);
		int vni3 = face.GetNormalIndex(2);
		glm::vec4 v1 = glm::vec4(this->GetVertex(vi1 - 1),1);
		glm::vec4 v2 = glm::vec4(this->GetVertex(vi2 - 1),1);
		glm::vec4 v3 = glm::vec4(this->GetVertex(vi3 - 1),1);
		glm::vec3 vv1(v1.x / v1.w, v1.y / v1.w, v1.z / v1.w);
		glm::vec3 vv2(v2.x / v2.w, v2.y / v2.w, v2.z / v2.w);
		glm::vec3 vv3(v3.x / v3.w, v3.y / v3.w, v3.z / v3.w);
		normals_[vni1-1] = glm::scale(glm::vec3(40, 40, 40)) * rWorldMatrix*rLocalMatrix*glm::vec4(this->GetVertexNormal(vni1-1),1);
		normals_[vni2 - 1] = glm::scale(glm::vec3(40, 40, 40)) * rWorldMatrix*rLocalMatrix*glm::vec4(this->GetVertexNormal(vni2-1),1);
		normals_[vni3 - 1] = glm::scale(glm::vec3(40, 40, 40)) * rWorldMatrix*rLocalMatrix*glm::vec4(this->GetVertexNormal(vni3-1),1);
	}
	Transformednormals_ = normals_;
















	//Transformednormals_ = normals_;
	//for (int i = 0; i < GetFacesCount(); i++) {
	//	int p1 = this->GetFace(i).GetVertexIndex(0)-1;
	//	int p2 = this->GetFace(i).GetVertexIndex(1)-1;
	//	int p3 = this->GetFace(i).GetVertexIndex(2)-1;
	//	glm::vec3 v1 = this->GetVertex(p1 ), v2 = this->GetVertex(p2 ), v3 = this->GetVertex(p3 );
	//	int n1 = this->GetFace(i).GetNormalIndex(0)-1;
	//	int n2 = this->GetFace(i).GetNormalIndex(1)-1;
	//	int n3 = this->GetFace(i).GetNormalIndex(2)-1;
	//	glm::vec3 vn1 = this->GetVertexNormal(n1), vn2 = this->GetVertexNormal(n2 ), vn3 = this->GetVertexNormal(n3);
	//	glm::vec4 vnn1=glm::vec4(vn1.x, vn1.y, vn1.z, 1);
	//	glm::vec4 vnn2 = glm::vec4(vn2.x, vn2.y, vn2.z, 1);
	//	glm::vec4 vnn3 = glm::vec4(vn3.x, vn3.y, vn3.z, 1);
	//	vnn1 = glm::scale(glm::vec3(40, 40, 40)) * vnn1;
	//	vnn2 = glm::scale(glm::vec3(40, 40, 40)) * vnn2;
	//	vnn3 = glm::scale(glm::vec3(40, 40, 40)) * vnn3;
	//	vn1.x = vnn1.x / vnn1.w;
	//	vn1.y = vnn1.y / vnn1.w;
	//	vn1.z = vnn1.z / vnn1.w;
	//	vn1 += v1;
	//
	//	vn2.x = vnn2.x / vnn2.w;
	//	vn2.y = vnn2.y / vnn2.w;
	//	vn2.z = vnn2.z / vnn2.w;
	//	vn2 += v2;
	//
	//	vn3.x = vnn3.x / vnn3.w;
	//	vn3.y = vnn3.y / vnn3.w;
	//	vn3.z = vnn3.z / vnn3.w;
	//	vn3 += v3;
	//
	//	normals_[n1] = vn1;
	//	normals_[n2] = vn2;
	//	normals_[n3] = vn3;
	//}
	//Transformednormals_ = normals_;
}

void MeshModel::TranslateAndScaleVertices(){
	glm::vec3 maxs = glm::vec3(vertices_[0][0], vertices_[0][1], vertices_[0][2]);
	glm::vec3 mins = glm::vec3(vertices_[0][0], vertices_[0][1], vertices_[0][2]);
	for (int i = 0; i < vertices_.size(); i++) {
		if (vertices_[i][0] < mins[0])
			mins[0] = vertices_[i][0];
		if (vertices_[i][1] < mins[1])
			mins[1] = vertices_[i][1];
		if (vertices_[i][2] < mins[2])
			mins[2] = vertices_[i][2];
	}
    if (mins[0] < 0) mins[0] *= -1;
	if (mins[1] < 0) mins[1] *= -1;
	if (mins[2] < 0) mins[2] *= -1;
	tLocalMatrix=glm::translate(glm::vec3(mins[0], mins[1], mins[2]));
	for (int i = 0; i < vertices_.size(); i++) {
		if (vertices_[i][0] > maxs[0])
			maxs[0] = vertices_[i][0];
		if (vertices_[i][1] > maxs[1])
			maxs[1] = vertices_[i][1];
		if (vertices_[i][2] > maxs[2])
			maxs[2] = vertices_[i][2];
	}
	maxs[0] = 350 / maxs[0];
	maxs[1] = 350 / maxs[1];
	maxs[2] = 350 / maxs[2];
	if (maxs[0] < maxs[1])maxs[1] = maxs[0];
	else maxs[0] = maxs[1];
	if (maxs[2] < maxs[1])maxs[1] = maxs[2];
	else maxs[2] = maxs[1];
	sLocalMatrix[0][0] = maxs[2];
	sLocalMatrix[1][1] = maxs[2];
	sLocalMatrix[2][2] = maxs[2];
	int i = 0, j = 0;
	glm::vec4 temp;
	glm::vec3 temp1;
	for (int k = 0; k < vertices_.size(); k++) {
		i = 0;
		temp = glm::vec4(vertices_[k][0], vertices_[k][1], vertices_[k][2], 1);
		temp = tLocalMatrix * temp;
		vertices_[k].x = temp.x / temp.w;
		vertices_[k].y = temp.y / temp.w;
		vertices_[k].z = temp.z / temp.w;
	}
	for (int k = 0; k < vertices_.size(); k++) {
		i = 0;
		temp = glm::vec4(vertices_[k][0], vertices_[k][1], vertices_[k][2], 1);
		temp = sLocalMatrix * temp;
		vertices_[k].x = temp.x / temp.w;
		vertices_[k].y = temp.y / temp.w;
		vertices_[k].z = temp.z / temp.w;
	}
	Transformedvertices_ = vertices_;
	sLocalMatrix[0][0] = 1;
	sLocalMatrix[1][1] = 1;
	sLocalMatrix[2][2] = 1;
	tLocalMatrix[3][0] = 0;
	tLocalMatrix[3][1] = 0;
	tLocalMatrix[3][2] = 0;
	maxX=minX = Transformedvertices_[0].x;
	maxY=minY = Transformedvertices_[0].y;
	maxZ = minZ = Transformedvertices_[0].z;
	for (int i = 1; i < vertices_.size(); i++) {
		if (Transformedvertices_[i].x > maxX)maxX = Transformedvertices_[i].x;
		if (Transformedvertices_[i].y > maxY)maxY = Transformedvertices_[i].y;
		if (Transformedvertices_[i].z > maxZ)maxZ = Transformedvertices_[i].z;
		if (Transformedvertices_[i].x < minX)minX = Transformedvertices_[i].x;
		if (Transformedvertices_[i].y < minY)minY = Transformedvertices_[i].y;
		if (Transformedvertices_[i].z < minZ)minZ = Transformedvertices_[i].z;
	}
	CalculateBoundingBox();
}

void MeshModel::ResetModel() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tWorldMatrix[i][j] = 0;
			rWorldMatrix[i][j] = 0;
			sWorldMatrix[i][j] = 0;
			tLocalMatrix[i][j] = 0;
			rLocalMatrix[i][j] = 0;
			sLocalMatrix[i][j] = 0;
			Transformation[i][j] =0;
			if (i == j) {
				tWorldMatrix[i][j] = 1;
				rWorldMatrix[i][j] = 1;
				sWorldMatrix[i][j] = 1;
				tLocalMatrix[i][j] = 1;
				rLocalMatrix[i][j] = 1;
				sLocalMatrix[i][j] = 1;
				Transformation[i][j] = 1;
			}
		}
	}
	Transformedvertices_ = vertices_;
	Transformednormals_ = normals_;
	CalculateBoundingBox();
	CalculateCenters();
	CalculateFacesNormals();

}

void MeshModel::TranslateVertices(char * lw,float x,float y,float z) {
	if (strcmp(lw, "world") == 0) {
		//tWorldMatrix[0][3] = x;
		//tWorldMatrix[1][3] = y;
		//tWorldMatrix[2][3] = z;
		tWorldMatrix = glm::translate(glm::vec3(x, y, z));
	}
	else {
		//tLocalMatrix[0][3] = x;
		//tLocalMatrix[1][3] = y;
		//tLocalMatrix[2][3] = z;
		tLocalMatrix = glm::translate(glm::vec3(x, y, z));
	}
	Transform();
}

void MeshModel::ScaleVertices(char* lw, float x, float y, float z) {
	if (strcmp(lw, "world") == 0) {
		//sWorldMatrix[0][0] = x;
		//sWorldMatrix[1][1] = y;
		//sWorldMatrix[2][2] = z;
		sWorldMatrix = glm::scale(glm::vec3(x, y, z));
	}
	else {
		//sLocalMatrix[0][0] = x;
		//sLocalMatrix[1][1] = y;
		//sLocalMatrix[2][2] = z;
		sLocalMatrix = glm::scale(glm::vec3(x, y, z));
	}
	Transform();
}

void MeshModel::Transform() {
	int i = 0, j = 0;
	glm::vec4 temp;
	glm::vec4 temp1;

		Transformation =  sWorldMatrix * rWorldMatrix * tWorldMatrix * sLocalMatrix * tLocalMatrix *rLocalMatrix ;
	for (int k = 0; k < vertices_.size(); k++) {
		temp = glm::vec4(vertices_[k][0], vertices_[k][1], vertices_[k][2], 1);
		temp = Transformation *temp;
		Transformedvertices_[k].x = temp.x/temp.w; 
		Transformedvertices_[k].y = temp.y / temp.w;
		Transformedvertices_[k].z = temp.z/temp.w;
	}

	//for (int k = 0; k < normals_.size(); k++) {
	//	temp1 = glm::vec4(normals_[k][0], normals_[k][1], normals_[k][2], 1);
	//	temp1 = Transformation * temp1;
	//	Transformednormals_[k].x = temp1.x / temp1.w;
	//	Transformednormals_[k].y = temp1.y / temp1.w;
	//	Transformednormals_[k].z = temp1.z / temp1.w;
	//}
	maxX = minX = Transformedvertices_[0].x;
	maxY = minY = Transformedvertices_[0].y;
	maxZ = minZ = Transformedvertices_[0].z;
	for (int i = 1; i < vertices_.size(); i++) {
		if (Transformedvertices_[i].x > maxX)maxX = Transformedvertices_[i].x;
		if (Transformedvertices_[i].y > maxY)maxY = Transformedvertices_[i].y;
		if (Transformedvertices_[i].z > maxZ)maxZ = Transformedvertices_[i].z;
		if (Transformedvertices_[i].x < minX)minX = Transformedvertices_[i].x;
		if (Transformedvertices_[i].y < minY)minY = Transformedvertices_[i].y;
		if (Transformedvertices_[i].z < minZ)minZ = Transformedvertices_[i].z;
	}
	CalculateBoundingBox();
	CalculateCenters();
	this->CalculateFacesNormals();
}

glm::vec3 MeshModel::GetVertex(int index)const {
	return Transformedvertices_[index];
}

glm::vec3 MeshModel::GetNormal(int index)const {
	return Facesnormals_[index];
}

glm::vec3 MeshModel::GetVertexNormal(int index)const {
	return Transformednormals_[index];
}

void MeshModel::RotateModel(char * lw,int axis, float angle) {
	glm::mat4x4 mat;
	if (axis == 2) {
		 //mat = { {cos(glm::radians(angle)),-sin(glm::radians(angle)),0,0},{sin(glm::radians(angle)),cos(glm::radians(angle)),0,0},{0,0,1,0},{0,0,0,1} };
		 mat = glm::rotate(glm::radians(angle), glm::vec3(0, 0, 1));
	}
	else if (axis == 1) {
		//mat = { {cos(glm::radians(angle)),0,-sin(glm::radians(angle)),0},{0,1,0,0} ,{sin(glm::radians(angle)),0,cos(glm::radians(angle)),0},{0,0,0,1} };
		mat = glm::rotate(glm::radians(angle), glm::vec3(0, 1, 0));
	}
	else {
	// mat = { {1,0,0,0}, {0,cos(glm::radians(angle)),-sin(glm::radians(angle)),0},{0,sin(glm::radians(angle)),cos(glm::radians(angle)),0},{0,0,0,1} };
	 mat = glm::rotate(glm::radians(angle),glm::vec3(1,0,0));
	}
	if (strcmp(lw, "local") == 0) {
		rLocalMatrix = mat* rLocalMatrix;
	}
	else {
		rWorldMatrix = mat* rWorldMatrix;
	}
	Transform();

}

void MeshModel::CalculateBoundingBox() {
	maxX = minX = Transformedvertices_[0].x;
	maxY = minY = Transformedvertices_[0].y;
	maxZ = minZ = Transformedvertices_[0].z;
	for (int i = 1; i < vertices_.size(); i++) {
		if (Transformedvertices_[i].x > maxX)maxX = Transformedvertices_[i].x;
		if (Transformedvertices_[i].y > maxY)maxY = Transformedvertices_[i].y;
		if (Transformedvertices_[i].z > maxZ)maxZ = Transformedvertices_[i].z;
		if (Transformedvertices_[i].x < minX)minX = Transformedvertices_[i].x;
		if (Transformedvertices_[i].y < minY)minY = Transformedvertices_[i].y;
		if (Transformedvertices_[i].z < minZ)minZ = Transformedvertices_[i].z;
	}
	BoundingBox.clear();
	BoundingBox.push_back(glm::vec3(minX, minY, minZ));
	BoundingBox.push_back(glm::vec3(maxX, minY, minZ));
	BoundingBox.push_back(glm::vec3(minX, maxY, minZ));
	BoundingBox.push_back(glm::vec3(maxX, maxY, minZ));
	BoundingBox.push_back(glm::vec3(minX, minY, maxZ));
	BoundingBox.push_back(glm::vec3(maxX, minY, maxZ));
	BoundingBox.push_back(glm::vec3(minX, maxY, maxZ));
	BoundingBox.push_back(glm::vec3(maxX, maxY, maxZ));
	
}

glm::vec3 MeshModel::GetVOfBoundingBox(int i) {
	return BoundingBox[i];
}

void MeshModel::CalculateCenters() {
	Centers.clear();
	for (int i = 0; i < this->GetFacesCount(); i++) {
		int p1 = this->GetFace(i).GetVertexIndex(0);
		int p2 = this->GetFace(i).GetVertexIndex(1);
		int p3 = this->GetFace(i).GetVertexIndex(2);
		glm::vec3 v1 = this->GetVertex(p1 - 1), v2 = this->GetVertex(p2 - 1), v3 = this->GetVertex(p3 - 1);
		float x = ((v1.x + v2.x + v3.x) / 3);
		float y = ((v1.y + v2.y + v3.y) / 3);
		float z = ((v1.z + v2.z + v3.z) / 3);
		Centers.push_back(glm::vec3(x,y,z));
	}
}

glm::vec3 MeshModel::GetCenter(int i) {
	  
		return Centers[i];
}

int MeshModel::GetVerticesCount() {
	return vertices_.size();
}