#include "MeshModel.h"
#include <stdio.h>
#include <iostream>
#include <cmath>

MeshModel::MeshModel(std::vector<Face> faces, std::vector<glm::vec3> vertices, std::vector<glm::vec3> normals, const std::string& model_name) :
	faces_(faces),
	vertices_(vertices),
	normals_(normals)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tWorldMatrix[i][j] = 0;
			rWorldMatrix[i][j] = 0;
			sWorldMatrix[i][j] = 0;
			tLocalMatrix[i][j] = 0;
			rLocalMatrix[i][j] = 0;
			sLocalMatrix[i][j] = 0;
			Transformation[i][j] = 0;
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

void MeshModel::MulMat(char* lw, float mat[4][4]) {
	float mat1[4][4];
	if (strcmp(lw, "local") == 0) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat1[i][j] = rLocalMatrix[i][j];
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				mat1[i][j] = rWorldMatrix[i][j];
			}
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			float sum = 0;
			for (int k = 0; k < 4; k++) {
				sum += mat1[i][k] * mat[k][j];
			}
			rLocalMatrix[i][j] = sum;
		}
	}
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
	tLocalMatrix[0][3] = mins[0];
	tLocalMatrix[1][3] = mins[1];
	tLocalMatrix[2][3] = mins[2];
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
	sLocalMatrix[0][0] = maxs[0];
	sLocalMatrix[1][1] = maxs[0];
	sLocalMatrix[2][2] = maxs[0];
	int i = 0, j = 0;
	glm::vec4 temp;
	glm::vec3 temp1;
	for (int k = 0; k < vertices_.size(); k++) {
		i = 0;
		temp = glm::vec4(vertices_[k][0], vertices_[k][1], vertices_[k][2], 1);
		while (i < 4) {
			float sum = 0;
			while (j < 4) {
				sum = sum + temp[j] * tLocalMatrix[i][j];
				j++;
			}
			if (i < 3)temp1[i] = sum;
			j = 0;
			i++;
		}
        vertices_[k] = temp1;
	}
	for (int k = 0; k < vertices_.size(); k++) {
		i = 0;
		temp = glm::vec4(vertices_[k][0], vertices_[k][1], vertices_[k][2], 1);
		while (i < 4) {
			float sum = 0;
			while (j < 4) {
				sum = sum + temp[j] * sLocalMatrix[i][j];
				j++;
			}
			if (i < 3)temp1[i] = sum;
			j = 0;
			i++;
		}
		vertices_[k] = temp1;
	}
	Transformedvertices_ = vertices_;
	sLocalMatrix[0][0] = 1;
	sLocalMatrix[1][1] = 1;
	sLocalMatrix[2][2] = 1;
	tLocalMatrix[0][3] = 0;
	tLocalMatrix[1][3] = 0;
	tLocalMatrix[2][3] = 0;
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
}

void MeshModel::TranslateVertices(char * lw,float x,float y,float z) {
	if (strcmp(lw, "world") == 0) {
		tWorldMatrix[0][3] = x;
		tWorldMatrix[1][3] = y;
		tWorldMatrix[2][3] = z;
	}
	else {
		tLocalMatrix[0][3] = x;
		tLocalMatrix[1][3] = y;
		tLocalMatrix[2][3] = z;
	}
	Transform();
}


void MeshModel::ScaleVertices(char* lw, float x, float y, float z) {
	if (strcmp(lw, "world") == 0) {
		sWorldMatrix[0][0] = x;
		sWorldMatrix[1][1] = y;
		sWorldMatrix[2][2] = z;
	}
	else {
		sLocalMatrix[0][0] = x;
		sLocalMatrix[1][1] = y;
		sLocalMatrix[2][2] = z;
	}
	Transform();
}

void MeshModel::Transform() {
	int i = 0, j = 0;
	glm::vec4 temp;
	glm::vec3 temp1;
	glm::mat4x4 m = sWorldMatrix * rWorldMatrix * tWorldMatrix*sLocalMatrix * rLocalMatrix * tLocalMatrix;
	for (int k = 0; k < vertices_.size(); k++) {
		i = 0;
		temp = glm::vec4(vertices_[k][0], vertices_[k][1], vertices_[k][2], 1);
		while (i < 4) {
			float sum = 0;
			while (j < 4) {
				sum =sum+ temp[j] * m[i][j];
				j++;
			}
			if(i<3)temp1[i] = sum;
			j = 0;
			i++;
		}
		Transformedvertices_[k] = temp1;
	}
}

glm::vec3 MeshModel::GetVertex(int index)const {
	return Transformedvertices_[index];
}

void MeshModel::RotateModel(char * lw,int axis, float angle) {
	glm::mat4x4 mat;
	if (axis == 2) {
		 mat = { {cos(glm::radians(angle)),-sin(glm::radians(angle)),0,0},{sin(glm::radians(angle)),cos(glm::radians(angle)),0,0},{0,0,1,0},{0,0,0,1} };

	}
	else if (axis == 1) {
		 mat = { {cos(glm::radians(angle)),0,-sin(glm::radians(angle)),0},{0,1,0,0} ,{sin(glm::radians(angle)),0,cos(glm::radians(angle)),0},{0,0,0,1} };
	
	}
	else {
	 mat = { {1,0,0,0}, {0,cos(glm::radians(angle)),-sin(glm::radians(angle)),0},{0,sin(glm::radians(angle)),cos(glm::radians(angle)),0},{0,0,0,1} };
	}
	if (strcmp(lw, "local") == 0) {
		rLocalMatrix =mat* rLocalMatrix;
	}
	else {
		rWorldMatrix *= mat;
	}
	Transform();

}