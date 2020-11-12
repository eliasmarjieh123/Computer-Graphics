#include "MeshModel.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals)
{
	lastScale[0] = 1;
	lastScale[1] = 1;
	lastTranslate[0] = 0;
	lastTranslate[1] = 0;
	latsRotationByX = 0;
	latsRotationByY = 0;
	latsRotationByZ = 0;
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

void MeshModel::MulMat(float TranslateMat[4][4]) {
	glm::vec3 temp;
	for (int i = 0; i < vertices_.size(); i++) {
		glm::vec4 v4 = glm::vec4(vertices_[i][0], vertices_[i][1], vertices_[i][2], 1);
		int j = 0, k = 0;
		while (k < 4) {
			float sum = 0;
			j = 0;
			while (j < 4) {
				sum =sum+ v4[j] * TranslateMat[k][j];
				j++;
			}
			if (k < 3)temp[k] = sum;
			k++;
		}
		vertices_[i] = temp;
	}
}

void MeshModel::TranslateVertices(int first,float x,float y,float z){
	if (first==1) {
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
		float mat[4][4] = { {1,0,0,mins[0]},{0,1,0,mins[1]},{0,0,1,mins[2]},{0,0,0,1} };
		MulMat(mat);
		Originalfaces_ = faces_;
		Originalnormals_ = normals_;
		Originalvertices_ = vertices_;
	}
	else {
		if (first != 2) {
			faces_ = Originalfaces_;
			vertices_ = Originalvertices_;
			normals_ = Originalnormals_;
			ScaleVertices(2, lastScale[0], lastScale[1], 1);
			RotateModel(2, 0, latsRotationByX);
			RotateModel(2, 1, latsRotationByY);
			RotateModel(2, 2, latsRotationByZ);
		}
		float mat[4][4] = { {1,0,0,x},{0,1,0,y},{0,0,1,z},{0,0,0,1} };
		MulMat(mat);
		lastTranslate[0] = x;
		lastTranslate[1] = y;
	}
}

void MeshModel::ScaleVertices(int first, float x, float y, float z)  {
	if (first==1) {
		glm::vec3 maxs = glm::vec3(vertices_[0][0], vertices_[0][1], vertices_[0][2]);
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
		float mat[4][4] = { {maxs[0],0,0,0},{0,maxs[0],0,0},{0,0,maxs[0],0},{0,0,0,1} };
		MulMat(mat);
		Originalfaces_ = faces_;
		Originalnormals_ = normals_;
		Originalvertices_ = vertices_;
	}
	else {
		if (first != 2) {
			faces_ = Originalfaces_;
			vertices_ = Originalvertices_;
			normals_ = Originalnormals_;
			TranslateVertices(2, lastTranslate[0], lastTranslate[1], 0);
			RotateModel(2, 0, latsRotationByX);
			RotateModel(2, 1, latsRotationByY);
			RotateModel(2, 2, latsRotationByZ);
		}
		float mat[4][4] = { {x,0,0,0},{0,y,0,0},{0,0,z,0},{0,0,0,1} };
		MulMat(mat);
		lastScale[0] = x;
		lastScale[1] = y;
	}
}

glm::vec3 MeshModel::GetVertex(int index)const {
	return vertices_[index];
}

void MeshModel::RotateModel(int Sync,int axis, float angle) {

	if (axis == 2){
		if (Sync != 2) {
			latsRotationByZ = angle;
			faces_ = Originalfaces_;
			vertices_ = Originalvertices_;
			normals_ = Originalnormals_;
			TranslateVertices(2, lastTranslate[0], lastTranslate[1], 0);
			ScaleVertices(2, lastScale[0], lastScale[1], 1);
			RotateModel(2, 0, latsRotationByX);
			RotateModel(2, 1, latsRotationByY);
		}
		float mat[4][4] = { {cos(angle),-sin(angle),0,0},{sin(angle),cos(angle),0,0},{0,0,1,0},{0,0,0,1} };
		MulMat(mat);
	}
	if (axis == 1) {
		if (Sync != 2) {
			latsRotationByY = angle;
			faces_ = Originalfaces_;
			vertices_ = Originalvertices_;
			normals_ = Originalnormals_;
			TranslateVertices(2, lastTranslate[0], lastTranslate[1], 0);
			ScaleVertices(2, lastScale[0], lastScale[1], 1);
			RotateModel(2, 0, latsRotationByX);
			RotateModel(2, 2, latsRotationByZ);
		}
		float mat[4][4] = { {cos(angle),0,-sin(angle),0},{0,1,0,0} ,{sin(angle),0,cos(angle),0},{0,0,0,1} };
		MulMat(mat);
	}
	if (axis == 0) {
		if (Sync != 2) {
			latsRotationByX = angle;
			faces_ = Originalfaces_;
			vertices_ = Originalvertices_;
			normals_ = Originalnormals_;
			TranslateVertices(2, lastTranslate[0], lastTranslate[1], 0);
			ScaleVertices(2, lastScale[0], lastScale[1], 1);
			RotateModel(2, 1, latsRotationByY);
			RotateModel(2, 2, latsRotationByZ);
		}
		float mat[4][4] = { {1,0,0,0}, {0,cos(angle),-sin(angle),0},{0,sin(angle),cos(angle),0},{0,0,0,1} };
		MulMat(mat);
	}
}