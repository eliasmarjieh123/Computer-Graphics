#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include "glm/gtc/matrix_transform.hpp"
#include <glm/gtx/transform.hpp>
#include "Renderer.h"
#include "InitShader.h"
#include <iostream>

#define INDEX(width,x,y,c) ((x)+(y)*(width))*3+(c)
#define Z_INDEX(width,x,y) ((x)+(y)*(width))
const double PI = 3.141592654;
Renderer::Renderer(int viewport_width, int viewport_height) :
	viewport_width_(viewport_width),
	viewport_height_(viewport_height)
{
	InitOpenGLRendering();
	CreateBuffers(viewport_width, viewport_height);
}

Renderer::~Renderer()
{
	delete[] color_buffer_;
}

void Renderer::PutPixel(int i, int j, const glm::vec3& color)
{
	if (i < 0) return; if (i >= viewport_width_) return;
	if (j < 0) return; if (j >= viewport_height_) return;
	
	color_buffer_[INDEX(viewport_width_, i, j, 0)] = color.x;
	color_buffer_[INDEX(viewport_width_, i, j, 1)] = color.y;
	color_buffer_[INDEX(viewport_width_, i, j, 2)] = color.z;
}

void Renderer::DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color)
{
	if (p1.x < p2.x) {
		float a, c, e = -(p2.x - p1.x);
		int x = p1.x, y = p1.y;
		//std::cout << p2.y-p1.y  <<"  "<< p2.x-p1.x<<std::endl;

		a = float(float(p2.y - p1.y) / float(p2.x - p1.x));
		if (a > 0 && a <= 1) {
			c = p1.y + a * p1.x;
			while (x <= p2.x) {
				if (e > 0) {
					y++;
					e = e - 2 * (p2.x - p1.x);
				}
				PutPixel(x, y, color);
				x++;
				e = e + 2 * (p2.y - p1.y);
			}
		}

		else if (a > 1) {
			int temp = y;
			y = x;
			x = temp;
			c = p1.x + a * p1.y;
			while (x <= p2.y) {
				if (e > 0) {
					y++;
					e = e - 2 * (p2.y - p1.y);
				}
				PutPixel(y, x, color);
				x++;
				e = e + 2 * (p2.x - p1.x);
			}
		}

		else if (a >= -1 && a <= 0) {
			c = p1.y + a * p1.x;
			while (x <= p2.x) {
				if (e > 0) {
					y--;
					e = e - 2 * (p2.x - p1.x);
				}
				PutPixel(x, y, color);
				x++;
				e = e + -2 * (p2.y - p1.y);
			}

		}

		else {
			int temp = y;
			y = x;
			x = temp;
			c = p1.x + a * p1.y;
			while (x >= p2.y) {
				if (e > 0) {
					y++;
					e = e + 2 * (p2.y - p1.y);
				}
				PutPixel(y, x, color);
				x--;
				e = e + 2 * (p2.x - p1.x);
			}

		}
	}
	else {
		float a, c, e = -(p1.x - p2.x);
		int x = p2.x, y = p2.y;
		//std::cout << p2.y-p1.y  <<"  "<< p2.x-p1.x<<std::endl;

		a = float(float(p1.y - p2.y) / float(p1.x - p2.x));
		if (a > 0 && a <= 1) {
			c = p2.y + a * p2.x;
			while (x <= p1.x) {
				if (e > 0) {
					y++;
					e = e - 2 * (p1.x - p2.x);
				}
				PutPixel(x, y, color);
				x++;
				e = e + 2 * (p1.y - p2.y);
			}
		}

		else if (a > 1) {
			int temp = y;
			y = x;
			x = temp;
			c = p2.x + a * p2.y;
			while (x <= p1.y) {
				if (e > 0) {
					y++;
					e = e - 2 * (p1.y - p2.y);
				}
				PutPixel(y, x, color);
				x++;
				e = e + 2 * (p1.x - p2.x);
			}
		}

		else if (a >= -1 && a <= 0) {
			c = p2.y + a * p2.x;
			while (x <= p1.x) {
				if (e > 0) {
					y--;
					e = e - 2 * (p1.x - p2.x);
				}
				PutPixel(x, y, color);
				x++;
				e = e + -2 * (p1.y - p2.y);
			}

		}

		else {
			int temp = y;
			y = x;
			x = temp;
			c = p2.x + a * p2.y;
			while (x >= p1.y) {
				if (e > 0) {
					y++;
					e = e + 2 * (p1.y - p2.y);
				}
				PutPixel(y, x, color);
				x--;
				e = e + 2 * (p1.x - p2.x);
			}

		}

	}
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
}

void Renderer::DrawFaces(glm::mat4x4 Transformation, MeshModel& mesh) {
	glm::vec4 v11 = glm::vec4(mesh.GetVertex(0), 1.f);
	v11 = Transformation * v11;
	v11.x = v11.x / v11.w;
	v11.y = v11.y / v11.w;
	v11.z = v11.z / v11.w;
	mesh.SetMinX(v11.x);
	mesh.SetMinX(v11.x);
	mesh.SetMinX(v11.x);
	mesh.SetMinY(v11.y);
	mesh.SetMinY(v11.y);
	mesh.SetMinY(v11.y);
	mesh.SetMinZ(v11.z);
	mesh.SetMinZ(v11.z);
	mesh.SetMinZ(v11.z);
	mesh.SetMaxX(v11.x);
	mesh.SetMaxX(v11.x);
	mesh.SetMaxX(v11.x);
	mesh.SetMaxY(v11.y);
	mesh.SetMaxY(v11.y);
	mesh.SetMaxY(v11.y);
	mesh.SetMaxZ(v11.z);
	mesh.SetMaxZ(v11.z);
	mesh.SetMaxZ(v11.z);
	for (int i = 0; i < mesh.GetFacesCount(); i++) {
		int p1 = mesh.GetFace(i).GetVertexIndex(0);
		int p2 = mesh.GetFace(i).GetVertexIndex(1);
		int p3 = mesh.GetFace(i).GetVertexIndex(2);
		glm::vec4 v1 =  glm::vec4(mesh.GetVertex(p1 - 1), 1.f), v2 =  glm::vec4(mesh.GetVertex(p2 - 1), 1.f), v3 =  glm::vec4(mesh.GetVertex(p3 - 1), 1.f);
		v1 = Transformation *v1;
		v2 = Transformation *v2;
		v3 = Transformation *v3;
		v1.x = v1.x /v1.w;
		v2.x = v2.x /v2.w;
		v3.x = v3.x /v3.w;
		v1.y = v1.y/v1.w; 
		v2.y = v2.y/v2.w; 
		v3.y = v3.y/v3.w; 
		v1.z = v1.z / v1.w;
		v2.z = v2.z / v2.w;
		v3.z = v3.z / v3.w;
		if (v1.x < mesh.GetMinX()){mesh.SetMinX(v1.x);}
		if (v2.x < mesh.GetMinX()){mesh.SetMinX(v2.x);}
		if (v3.x < mesh.GetMinX()){mesh.SetMinX(v3.x);}
		if (v1.y < mesh.GetMinY()){mesh.SetMinY(v1.y);}
		if (v2.y < mesh.GetMinY()){mesh.SetMinY(v2.y);}
		if (v3.y < mesh.GetMinY()){mesh.SetMinY(v3.y);}
		if (v1.z < mesh.GetMinZ()){mesh.SetMinZ(v1.z);}
		if (v2.z < mesh.GetMinZ()){mesh.SetMinZ(v2.z);}
		if (v3.z < mesh.GetMinZ()){mesh.SetMinZ(v3.z);}
		if (v1.x > mesh.GetMaxX()){mesh.SetMaxX(v1.x);}
		if (v2.x > mesh.GetMaxX()){mesh.SetMaxX(v2.x);}
		if (v3.x > mesh.GetMaxX()){mesh.SetMaxX(v3.x);}
		if (v1.y > mesh.GetMaxY()){mesh.SetMaxY(v1.y);}
		if (v2.y > mesh.GetMaxY()){mesh.SetMaxY(v2.y);}
		if (v3.y > mesh.GetMaxY()){mesh.SetMaxY(v3.y);}
		if (v1.z > mesh.GetMaxZ()){mesh.SetMaxZ(v1.z);}
		if (v2.z > mesh.GetMaxZ()){mesh.SetMaxZ(v2.z);}
		if (v3.z > mesh.GetMaxZ()){mesh.SetMaxZ(v3.z);}
		if (v1.z > mesh.GetMaxW()) { mesh.SetMaxW(v1.w); }
		if (v2.z > mesh.GetMaxW()) { mesh.SetMaxW(v2.w); }
		if (v3.z > mesh.GetMaxW()) { mesh.SetMaxW(v3.w); }
		if (v1.z < mesh.GetMinW()) { mesh.SetMinW(v1.w); }
		if (v2.z < mesh.GetMinW()) { mesh.SetMinW(v2.w); }
		if (v3.z < mesh.GetMinW()) { mesh.SetMinW(v3.w); }
		glm::ivec2 point1 = glm::ivec2(v1.x, v1.y );
		glm::ivec2 point2 = glm::ivec2(v2.x,v2.y );
		glm::ivec2 point3 = glm::ivec2(v3.x,v3.y );
	    DrawLine(point1, point2, mesh.GetFaceColor(i));
		DrawLine(point1, point3, mesh.GetFaceColor(i));
		DrawLine(point3, point2, mesh.GetFaceColor(i));
	}
	mesh.CalculateBoundingBox();
}

bool Renderer::CheckIfLastFaceFromRight(int x, int y,int maxx) {
	while (x <= maxx) {
		if ((color_buffer_[INDEX(viewport_width_, x , y, 0)] != 1.0f ||
			color_buffer_[INDEX(viewport_width_, x , y, 1)] != 1.0f ||
			color_buffer_[INDEX(viewport_width_, x , y, 2)] != 1.0f)) {
			return 1;
		}
		x++;
	}
	return 0;
}

bool Renderer::PointInTriangle(int x,int y )
{
	if ((color_buffer_[INDEX(viewport_width_, x-1, y, 0)] != 1.0f ||
		color_buffer_[INDEX(viewport_width_, x-1, y, 1)] != 1.0f ||
		color_buffer_[INDEX(viewport_width_, x-1, y, 2)] != 1.0f)&& 
		(color_buffer_[INDEX(viewport_width_, x + 1, y, 0)] == 1.0f &&
		color_buffer_[INDEX(viewport_width_, x + 1, y, 1)] == 1.0f &&
		color_buffer_[INDEX(viewport_width_, x + 1, y, 2)] == 1.0f
		)) {
		return 1;
	}
	return 0;
}

void Renderer::FillTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int i,glm::mat4x4 t, MeshModel& mesh,glm::vec3 v,Scene& s) {
	int minx, miny, maxy, maxx, tempx, flag;
	glm::vec3 color,vn1,vn2,vn3,v1Color,v2Color,v3Color,PixelNormal;
	glm::vec3 position;
	Light l;
	maxx = std::max(v1.x, std::max(v2.x, v3.x));
	maxy = std::max(v1.y, std::max(v2.y, v3.y));
	minx = std::min(v1.x, std::min(v2.x, v3.x));
	miny = std::min(v1.y, std::min(v2.y, v3.y));
	if (mesh.GetShadingType() == 0) {
		color = glm::vec3(0, 0, 0);
		for (int x = 0; x < s.GetLightCount(); x++) {
			l = s.GetLight(x);
			if (l.IsActive()) {
				if (l.GetIfPoint()) {
					position = l.GetTransformation() * glm::vec4(l.GetPosition(), 1);
				}
				else {
					position = l.GetPosition();
				}
				if (l.GetIfPoint()) {
					color = color + CalculateColor(l.GetAlpha(), mesh.GetRotation() * (glm::vec4(mesh.GetNormal(i), 2) - glm::vec4(mesh.GetCenter(i), 1)), glm::normalize(glm::vec4(position, 1) - t * glm::vec4(mesh.GetCenter(i), 1)), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
				}
				else {
					color = color + CalculateColor(l.GetAlpha(), mesh.GetRotation() * (glm::vec4(mesh.GetNormal(i), 2) - glm::vec4(mesh.GetCenter(i), 1)), glm::normalize(position), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
				}
			}
		}
			while (miny <= maxy) {
				tempx = minx;
				while (tempx <= maxx) {
					if (PointInTriangle(glm::vec3(tempx, miny, 0), v1, v2, v3)) {
						glm::vec3 Z = CalculateZ(glm::vec3(tempx, miny, 0), v1, v2, v3, v1, v2, v3);
						if (mesh.GetIfZbufferAlgo()) {
							if (Z.z < Z_buffer_[(miny)*viewport_width_ + tempx]) {
								if (minz > Z.z)minz = Z.z;
								if (maxz < Z.z)maxz = Z.z;
								Z_buffer_[(miny)*viewport_width_ + tempx] = Z.z;
								PutPixel(tempx, miny, color);
							}
						}
						else {
							PutPixel(tempx, miny, color);
						}
					}
					tempx++;
				}
				miny++;
			}
	}

	else if(mesh.GetShadingType()==1){
		vn1 = mesh.GetVertexNormal(mesh.GetFace(i).GetNormalIndex(0) - 1);
		vn2 = mesh.GetVertexNormal(mesh.GetFace(i).GetNormalIndex(1) - 1);
		vn3 = mesh.GetVertexNormal(mesh.GetFace(i).GetNormalIndex(2) - 1);

		while (miny <= maxy) {
			tempx = minx;
			while (tempx <= maxx) {
				if (PointInTriangle(glm::vec3(tempx, miny, 0), v1, v2, v3)) {
					glm::vec3 Z = CalculateZ(glm::vec3(tempx, miny, 0), v1, v2, v3, v1, v2, v3);
					color = glm::vec3(0, 0, 0);
					for (int x = 0; x < s.GetLightCount(); x++) {
						l = s.GetLight(x);
						if (l.IsActive()) {
							if (l.GetIfPoint()) {
								position = l.GetTransformation() * glm::vec4(l.GetPosition(), 1);
								v1Color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(vn1, 1), glm::normalize(position - v1), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
								v2Color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(vn2, 1), glm::normalize(position - v2), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
								v3Color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(vn3, 1), glm::normalize(position - v3), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
							}
							else {
								position = l.GetPosition();
								v1Color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(vn1, 1), glm::normalize(position), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
								v2Color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(vn2, 1), glm::normalize(position), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
								v3Color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(vn3, 1), glm::normalize(position), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
							}
							color = color + CalculateZ(Z, v1, v2, v3, v1Color, v2Color, v3Color);
						}
					}
					if (color.x > 1)color.x = 1;
					if (color.y > 1)color.y = 1;
					if (color.z > 1)color.z = 1;
					if (mesh.GetIfZbufferAlgo()) {
						if (Z.z < Z_buffer_[(miny)*viewport_width_ + tempx]) {
							if (minz > Z.z)minz = Z.z;
							if (maxz < Z.z)maxz = Z.z;
							Z_buffer_[(miny)*viewport_width_ + tempx] = Z.z;
							PutPixel(tempx, miny, color);
						}
					}
					else {
						PutPixel(tempx, miny, color);
					}
				}
				tempx++;
			}
			miny++;
		}
	}

	else {
		vn1 = mesh.GetVertexNormal(mesh.GetFace(i).GetNormalIndex(0) - 1);
		vn2 = mesh.GetVertexNormal(mesh.GetFace(i).GetNormalIndex(1) - 1);
		vn3 = mesh.GetVertexNormal(mesh.GetFace(i).GetNormalIndex(2) - 1);
		while (miny <= maxy) {
			tempx = minx;
			while (tempx <= maxx) {
				if (PointInTriangle(glm::vec3(tempx, miny, 0), v1, v2, v3)) {
					glm::vec3 Z = CalculateZ(glm::vec3(tempx, miny, 0), v1, v2, v3, v1, v2, v3);
					PixelNormal = CalculateZ(glm::vec3(tempx, miny, 0), v1, v2, v3, vn1, vn2, vn3);
					color = glm::vec3(0, 0, 0);
					for (int x = 0; x < s.GetLightCount(); x++) {
						l = s.GetLight(x);
						if (l.IsActive()) {
							if (l.GetIfPoint()) {
								position = l.GetTransformation() * glm::vec4(l.GetPosition(), 1);
								color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(PixelNormal, 1), glm::normalize(position - Z), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
							}
							else {
								position = l.GetPosition();
								color = CalculateColor(l.GetAlpha(), mesh.GetRotation() * glm::vec4(PixelNormal, 1), glm::normalize(position), mesh.GetAmbientColor(), mesh.GetDiffuseColor(), mesh.GetSpecularColor(), l.GetAmbientColor(), l.GetDiffuseColor(), l.GetSpecularColor(), v);
							}
						}
					}
					if (mesh.GetIfZbufferAlgo()) {
						if (Z.z < Z_buffer_[(miny)*viewport_width_ + tempx]) {
							if (minz > Z.z)minz = Z.z;
							if (maxz < Z.z)maxz = Z.z;
							Z_buffer_[(miny)*viewport_width_ + tempx] = Z.z;
							PutPixel(tempx, miny, color);
						}
					}
					else {
						PutPixel(tempx, miny, color);
					}
				}
				tempx++;
			}
			miny++;
		}
	}
}

void Renderer::DrawFaces2(glm::mat4x4 Transformation,glm::mat4x4 view, MeshModel& mesh,bool ortho,Scene& s,glm::vec3 v) {
	glm::vec4 v11 = glm::vec4(mesh.GetVertex(0), 1.f);
	v11 = view*Transformation * v11;
	v11.x = v11.x / v11.w;
	v11.y = v11.y / v11.w;
	v11.z = v11.z / v11.w;
	mesh.SetMinX(v11.x);
	mesh.SetMinX(v11.x);
	mesh.SetMinX(v11.x);
	mesh.SetMinY(v11.y);
	mesh.SetMinY(v11.y);
	mesh.SetMinY(v11.y);
	mesh.SetMinZ(v11.z);
	mesh.SetMinZ(v11.z);
	mesh.SetMinZ(v11.z);
	mesh.SetMaxX(v11.x);
	mesh.SetMaxX(v11.x);
	mesh.SetMaxX(v11.x);
	mesh.SetMaxY(v11.y);
	mesh.SetMaxY(v11.y);
	mesh.SetMaxY(v11.y);
	mesh.SetMaxZ(v11.z);
	mesh.SetMaxZ(v11.z);
	mesh.SetMaxZ(v11.z);
	for (int i = 0; i < mesh.GetFacesCount(); i++) {
		int p1 = mesh.GetFace(i).GetVertexIndex(0);
		int p2 = mesh.GetFace(i).GetVertexIndex(1);
		int p3 = mesh.GetFace(i).GetVertexIndex(2);
		glm::vec4 v1 = glm::vec4(mesh.GetVertex(p1 - 1), 1.f), v2 = glm::vec4(mesh.GetVertex(p2 - 1), 1.f), v3 = glm::vec4(mesh.GetVertex(p3 - 1), 1.f);
		v1 = Transformation * v1;
		v2 = Transformation * v2;
		v3 = Transformation * v3;
		v1 = view * v1;
		v2 = view * v2;
		v3 = view * v3;
		v1.x = v1.x / v1.w;
		v2.x = v2.x / v2.w;
		v3.x = v3.x / v3.w;
		v1.y = v1.y / v1.w;
		v2.y = v2.y / v2.w;
		v3.y = v3.y / v3.w;
		if (ortho) {
			v1.z = -v1.z / v1.w;
			v2.z = -v2.z / v2.w;
			v3.z = -v3.z / v3.w;
		}
		else {
			v1.z = v1.z / v1.w;
			v2.z = v2.z / v2.w;
			v3.z = v3.z / v3.w;
		}
		if (v1.x < mesh.GetMinX()) { mesh.SetMinX(v1.x); }
		if (v2.x < mesh.GetMinX()) { mesh.SetMinX(v2.x); }
		if (v3.x < mesh.GetMinX()) { mesh.SetMinX(v3.x); }
		if (v1.y < mesh.GetMinY()) { mesh.SetMinY(v1.y); }
		if (v2.y < mesh.GetMinY()) { mesh.SetMinY(v2.y); }
		if (v3.y < mesh.GetMinY()) { mesh.SetMinY(v3.y); }
		if (v1.z < mesh.GetMinZ()) { mesh.SetMinZ(v1.z); }
		if (v2.z < mesh.GetMinZ()) { mesh.SetMinZ(v2.z); }
		if (v3.z < mesh.GetMinZ()) { mesh.SetMinZ(v3.z); }
		if (v1.x > mesh.GetMaxX()) { mesh.SetMaxX(v1.x); }
		if (v2.x > mesh.GetMaxX()) { mesh.SetMaxX(v2.x); }
		if (v3.x > mesh.GetMaxX()) { mesh.SetMaxX(v3.x); }
		if (v1.y > mesh.GetMaxY()) { mesh.SetMaxY(v1.y); }
		if (v2.y > mesh.GetMaxY()) { mesh.SetMaxY(v2.y); }
		if (v3.y > mesh.GetMaxY()) { mesh.SetMaxY(v3.y); }
		if (v1.z > mesh.GetMaxZ()) { mesh.SetMaxZ(v1.z); }
		if (v2.z > mesh.GetMaxZ()) { mesh.SetMaxZ(v2.z); }
		if (v3.z > mesh.GetMaxZ()) { mesh.SetMaxZ(v3.z); }
		if (v1.z > mesh.GetMaxW()) { mesh.SetMaxW(v1.w); }
		if (v2.z > mesh.GetMaxW()) { mesh.SetMaxW(v2.w); }
		if (v3.z > mesh.GetMaxW()) { mesh.SetMaxW(v3.w); }
		if (v1.z < mesh.GetMinW()) { mesh.SetMinW(v1.w); }
		if (v2.z < mesh.GetMinW()) { mesh.SetMinW(v2.w); }
		if (v3.z < mesh.GetMinW()) { mesh.SetMinW(v3.w); }
		FillTriangle(v1, v2, v3, i, view * Transformation,mesh,v,s);
	}
	mesh.CalculateBoundingBox();
}

void Renderer::DrawVertexNormals(glm::mat4x4 Transformation, MeshModel& mesh) {
	for (int i = 0; i < mesh.GetFacesCount(); i++) {
		Face face = mesh.GetFace(i);
		int vi1 = face.GetVertexIndex(0);
		int vi2 = face.GetVertexIndex(1);
		int vi3 = face.GetVertexIndex(2);
		int vni1 = face.GetNormalIndex(0);
		int vni2 = face.GetNormalIndex(1);
		int vni3 = face.GetNormalIndex(2);
		glm::vec4 v1 = Transformation * glm::vec4(mesh.GetVertex(vi1 - 1), 1);
		glm::vec4 v2 = Transformation * glm::vec4(mesh.GetVertex(vi2 - 1), 1);
		glm::vec4 v3 = Transformation * glm::vec4(mesh.GetVertex(vi3 - 1), 1);
		glm::vec4 vn1 = glm::scale(glm::vec3(30,30,30))*glm::vec4(mesh.GetVertexNormal(vni1 - 1), 1);
		glm::vec4 vn2 = glm::scale(glm::vec3(30,30,30))*glm::vec4(mesh.GetVertexNormal(vni2 - 1), 1);
		glm::vec4 vn3 = glm::scale(glm::vec3(30,30,30))*glm::vec4(mesh.GetVertexNormal(vni3 - 1), 1);
		DrawLine(glm::ivec2(v1.x , v1.y), glm::ivec2((vn1.x / vn1.w) + v1.x, (vn1.y / vn1.w) + v1.y), mesh.Get_ShowVertexNormalsColor());
		DrawLine(glm::ivec2(v2.x , v2.y), glm::ivec2((vn2.x / vn2.w) + v2.x, (vn2.y / vn2.w) + v2.y), mesh.Get_ShowVertexNormalsColor());
		DrawLine(glm::ivec2(v3.x , v3.y), glm::ivec2((vn3.x / vn3.w) + v3.x, (vn3.y / vn3.w) + v3.y), mesh.Get_ShowVertexNormalsColor());
	}
}

void Renderer::DrawFaceNormals(glm::mat4x4 Transformation,MeshModel& mesh) {
	for (int i = 0; i < mesh.GetFacesCount(); i++) {
		glm::vec4 v1 = glm::vec4(mesh.GetCenter(i),1), v4 = glm::vec4(mesh.GetNormal(i),1);
		v4 = Transformation * v4;
		v4.x = v4.x / v4.w;
		v4.y = v4.y / v4.w;
		v4.z = v4.z / v4.w;
		v1 = Transformation * v1;
		v1.x = v1.x / v1.w;
		v1.y = v1.y / v1.w;
		v1.z = v1.z / v1.w;
		glm::ivec2 point1 = glm::ivec2(v1[0], v1[1]);
		glm::ivec2 point4 = glm::ivec2(v4[0], v4[1]);
		DrawLine(point4, point1, mesh.Get_ShowFaceNormalsColor());
	}
}

void Renderer::DrawBoundingBox(Camera& mesh) {
	glm::vec4 v1 = mesh.GetVOfBoundingBox(0), v2 = mesh.GetVOfBoundingBox(1), v3 = mesh.GetVOfBoundingBox(2), v4 = mesh.GetVOfBoundingBox(3);
	glm::vec4 v5 = mesh.GetVOfBoundingBox(4), v6 = mesh.GetVOfBoundingBox(5), v7 = mesh.GetVOfBoundingBox(6), v8 = mesh.GetVOfBoundingBox(7);
	//std::cout << v3.y << std::endl;
	glm::ivec2 point1 = glm::ivec2(v1.x, v1.y);
	glm::ivec2 point2 = glm::ivec2(v2.x, v2.y);
	glm::ivec2 point3 = glm::ivec2(v3.x, v3.y);
	glm::ivec2 point4 = glm::ivec2(v4.x, v4.y);
	glm::ivec2 point5;
	glm::ivec2 point6;
	glm::ivec2 point7;
	glm::ivec2 point8;
	if (mesh.GetIfOrthographicProjection()) {
		point5 = glm::ivec2(v5.x , v5.y);
		point6 = glm::ivec2(v6.x , v6.y);
		point7 = glm::ivec2(v7.x , v7.y);
		point8 = glm::ivec2(v8.x , v8.y);
	}
	else {
		point5 = glm::ivec2(v5.x / v5.z, v5.y / v5.z);
		point6 = glm::ivec2(v6.x / v6.z, v6.y / v6.z);
		point7 = glm::ivec2(v7.x / v7.z, v7.y / v7.z);
		point8 = glm::ivec2(v8.x / v8.z, v8.y / v8.z);
	}
	DrawLine(point1, point2, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point1, point3, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point4, point2, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point3, point4, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point5, point6, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point5, point7, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point8, point6, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point7, point8, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point1, point5, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point2, point6, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point3, point7, mesh.Get_ShowBoundingBoxColor());
	DrawLine(point4, point8, mesh.Get_ShowBoundingBoxColor());
}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenGLBuffer(); //Do not remove this line.
	color_buffer_ = new float[3 * w * h];
	Z_buffer_ = new float[ w * h];
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
	ClearZbuffer(w, h);
}

//##############################
//##OpenGL stuff. Don't touch.##
//##############################

// Basic tutorial on how opengl works:
// http://www.opengl-tutorial.org/beginners-tutorials/tutorial-2-the-first-triangle/
// don't linger here for now, we will have a few tutorials about opengl later.
void Renderer::InitOpenGLRendering()
{
	// Creates a unique identifier for an opengl texture.
	glGenTextures(1, &gl_screen_tex_);

	// Same for vertex array object (VAO). VAO is a set of buffers that describe a renderable object.
	glGenVertexArrays(1, &gl_screen_vtc_);

	GLuint buffer;

	// Makes this VAO the current one.
	glBindVertexArray(gl_screen_vtc_);

	// Creates a unique identifier for a buffer.
	glGenBuffers(1, &buffer);

	// (-1, 1)____(1, 1)
	//	     |\  |
	//	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
	//	     |__\|
	// (-1,-1)    (1,-1)
	const GLfloat vtc[]={
		-1, -1,
		 1, -1,
		-1,  1,
		-1,  1,
		 1, -1,
		 1,  1
	};

	const GLfloat tex[]={
		0,0,
		1,0,
		0,1,
		0,1,
		1,0,
		1,1};

	// Makes this buffer the current one.
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// This is the opengl way for doing malloc on the gpu. 
	glBufferData(GL_ARRAY_BUFFER, sizeof(vtc)+sizeof(tex), NULL, GL_STATIC_DRAW);

	// memcopy vtc to buffer[0,sizeof(vtc)-1]
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vtc), vtc);

	// memcopy tex to buffer[sizeof(vtc),sizeof(vtc)+sizeof(tex)]
	glBufferSubData(GL_ARRAY_BUFFER, sizeof(vtc), sizeof(tex), tex);

	// Loads and compiles a sheder.
	GLuint program = InitShader( "vshader.glsl", "fshader.glsl" );

	// Make this program the current one.
	glUseProgram(program);

	// Tells the shader where to look for the vertex position data, and the data dimensions.
	GLint  vPosition = glGetAttribLocation( program, "vPosition" );
	glEnableVertexAttribArray( vPosition );
	glVertexAttribPointer( vPosition,2,GL_FLOAT,GL_FALSE,0,0 );

	// Same for texture coordinates data.
	GLint  vTexCoord = glGetAttribLocation( program, "vTexCoord" );
	glEnableVertexAttribArray( vTexCoord );
	glVertexAttribPointer( vTexCoord,2,GL_FLOAT,GL_FALSE,0,(GLvoid *)sizeof(vtc) );

	//glProgramUniform1i( program, glGetUniformLocation(program, "texture"), 0 );

	// Tells the shader to use GL_TEXTURE0 as the texture id.
	glUniform1i(glGetUniformLocation(program, "texture"),0);
}

void Renderer::CreateOpenGLBuffer()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex_);

	// malloc for a texture on the gpu.
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, viewport_width_, viewport_height_, 0, GL_RGB, GL_FLOAT, NULL);
	glViewport(0, 0, viewport_width_, viewport_height_);
}

void Renderer::SwapBuffers()
{
	// Makes GL_TEXTURE0 the current active texture unit
	glActiveTexture(GL_TEXTURE0);

	// Makes glScreenTex (which was allocated earlier) the current texture.
	glBindTexture(GL_TEXTURE_2D, gl_screen_tex_);

	// memcopy's colorBuffer into the gpu.
	glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, viewport_width_, viewport_height_, GL_RGB, GL_FLOAT, color_buffer_);

	// Tells opengl to use mipmapping
	glGenerateMipmap(GL_TEXTURE_2D);

	// Make glScreenVtc current VAO
	glBindVertexArray(gl_screen_vtc_);

	// Finally renders the data.
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Renderer::ClearColorBuffer(const glm::vec3& color)
{
	for (int i = 0; i < viewport_width_; i++)
	{
		for (int j = 0; j < viewport_height_; j++)
		{
			PutPixel(i, j, color);
		}
	}
}

void Renderer::ClearZbuffer(int w,int h) {
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			Z_buffer_[i * w + j] =1.0f;

	this->minz = FLT_MAX;
	this->maxz = FLT_MIN;
}

void Renderer::Render(Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width_ / 2;
	int half_height = viewport_height_ / 2;
	int thickness = 15;
	int r = 10, steps = 50;
	float angle = 2.f * PI / steps;
	float w =float( GetViewportWidth());
	float h = float(GetViewportHeight());
	Light l;
	ClearZbuffer(w,h);
	if (scene.GetLightCount() > 0) {
		for (int j = 0; j < scene.GetLightCount(); j++) {
			l = scene.GetLight(j);
			if (l.IsActive()) {
				if (l.GetIfPoint()) {
					for (int i = 0; i <= steps; i++) {
						glm::vec2 point1 = l.GetTransformation() * glm::vec4(l.GetPosition(), 1);
						glm::ivec2 point2 = glm::ivec2(point1.x + r * sin(angle * i), point1.y + r * cos(angle * i));
						DrawLine(point1, point2, l.GetAmbientColor());
					}
				}
			}
		}
	}
	if (scene.GetCameraCount()>0) {
		Camera cam = scene.GetActiveCamera();
		glm::mat4x4 CamTransformation = cam.GetViewTransformation();
		glm::mat4x4 LookAt = cam.GetCameraLookAt();
		glm::mat4x4 ViewPort = glm::scale(glm::vec3(half_width,half_height,1))*glm::translate(glm::vec3(1,1,1));
		if (!cam.GetIfOrthographicProjection()) {
			ViewPort = glm::scale(glm::vec3(half_width, half_height, 1)) * glm::translate(glm::vec3(1, 1, 0));
		}
		glm::mat4x4 ViewT = cam.GetViewTransformation();
		glm::mat4x4 Projection = cam.GetProjectionTransformation();
		glm::mat4x4 ModelTransformation = cam.GetTransformation();
		glm::mat4x4 World = cam.GetWorldTransformation();
		glm::mat4x4 Scale = cam.GetModelScale();
		glm::mat4x4 t =  Projection  * LookAt * glm::inverse(ViewT) *ModelTransformation*Scale;
		float height_ = 20.0f / 1.7777f;
		//t= glm::ortho(-20.0f / 2, 20.0f / 2, - height_ / 2, height_ / 2, 0.1f, -1000.f)* glm::lookAt(glm::vec3(0,0,10), glm::vec3(0,0,0), glm::vec3(0,1,0))* glm::inverse(ViewT) * ModelTransformation;
		DrawFaces2(t,ViewPort, cam, cam.GetIfOrthographicProjection(),scene,cam.GetEye());
		if (cam.GetIfGrayScale()) {
			ZBufferGrayscale();
		}
		if(cam.Get_ShowBoundingBox())DrawBoundingBox(cam);
		if (cam.Get_ShowFaceNormals())DrawFaceNormals(ViewPort * t, cam);
		if (cam.Get_ShowVertexNormals())DrawVertexNormals(ViewPort * t, cam);
		if (scene.IsFogActivated())Fog(scene);
	}

    ///////////////////////////////this loop test Bresenham's algorithm

	/////////////////////////////////this loop prints 16 circles in each other

	//for (int R = 30; R < 200; R += 10) {
	//	for (int i = 0; i <= steps; i++) {
	//		glm::ivec2 point2 = glm::ivec2(point1.x + R * sin(angle * i), point1.y + R * cos(angle * i));
	//		PutPixel(point2.x, point2.y, glm::vec3(0, 0, 0));
	//	}
	//}


	/////////////////////////////////this two loops are for showing the cross

	//for(int i = 0; i < viewport_width_; i++)
	//{
	//	for (int j = half_height - thickness; j < half_height + thickness; j++)
	//	{
	//		PutPixel(i, j, glm::vec3(1, 1, 0));
	//	}
	//}
	//for (int i = 0; i < viewport_height_; i++)
	//{
	//	for (int j = half_width - thickness; j < half_width + thickness; j++)
	//	{
	//		PutPixel(j, i, glm::vec3(1, 0, 1));
	//	}
	//}
}

int Renderer::GetViewportWidth() const
{
	return viewport_width_;
}

int Renderer::GetViewportHeight() const
{
	return viewport_height_;
}

glm::mat4x4 Renderer::GetViewPortTransformation()
{
	return glm::mat4x4(GetViewportWidth()/2,0,0,0,0,GetViewportHeight()/2,0,0,0,0,1,0,(GetViewportWidth()-1)/2,(GetViewportHeight()-1)/2,0,1);
}

glm::vec3 Renderer::CalculateZ(glm::vec3 p,glm::vec3 v1, glm::vec3 v2, glm::vec3 v3,glm::vec3 val1,glm::vec3 val2,glm::vec3 val3) {
	float A , A1 = CalcArea(p, v2, v3), A2 = CalcArea(p, v1, v3), A3 = CalcArea(p, v1, v2);
	A = A1 + A2 + A3;
	return ((A1 / A * val1) + (A2 / A * val2) + (A3 / A * val3));
}

void Renderer::ZBufferGrayscale()
{
	float color = 0.f, a = 1 / (maxz - minz), b = -a * minz;
	//std::cout << minz << std::endl;
	//std::cout << maxz << std::endl;
	//std::cout <<  std::endl;
	for (int i = 0; i < viewport_height_; i++)
	{
		for (int j = 0; j < viewport_width_; j++)
		{
			if ((color_buffer_[INDEX(viewport_width_, j, i, 0)] != 1.0f ||
				color_buffer_[INDEX(viewport_width_, j, i, 1)] != 1.0f ||
				color_buffer_[INDEX(viewport_width_, j, i, 2)] != 1.0f))
			{
				color = a * Z_buffer_[i * viewport_width_ + j] + b;
				color =  1-color;
				//std::cout << color << std::endl;
				PutPixel(j, i, glm::vec3(color,color,color));
			}
			else
				PutPixel(j, i, glm::vec3(0.0f,0.0f,0.0f));
		}
	}
}

float Renderer::CalcArea(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3) {
	return abs(((v2.x - v1.x) * (v3.y - v1.y) - (v3.x - v1.x) * (v2.y - v1.y)) / 2.f);
	//return abs((v1.x * (v2.y - v3.y) + v2.x * (v3.y - v1.y) + v3.x * (v2.y - v1.y)) / 2.0f);
}

bool Renderer::PointInTriangle(glm::vec3 p, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3)
{
	 auto dX = p.x - p3.x;
	 auto dY = p.y - p3.y;
	 auto dX21 = p3.x - p2.x;
	 auto dY12 = p2.y - p3.y;
	 auto D = dY12 * (p1.x - p3.x) + dX21 * (p1.y - p3.y);
	 auto s = dY12 * dX + dX21 * dY;
	 auto t = (p3.y - p1.y) * dX + (p1.x - p3.x) * dY;
	 if (D < 0) return s <= 0 && t <= 0 && s + t >= D;
	 return s >= 0 && t >= 0 && s + t <= D;

}

glm::vec3 Renderer::CalculateColor(int a,glm::vec3 normal,glm::vec3 LightPosition, glm::vec3 ModelAmbient, glm::vec3 ModelDiffuse, glm::vec3 ModelSpecular, glm::vec3 LightAmbient, glm::vec3 LightDiffuse, glm::vec3 LightSpecular,glm::vec3 v) {
	 int alpha = a;
	 glm::vec3 Ambient, Diffuse, Specular,r,color;
	 float angle1,angle=(normal.x*LightPosition.x+ normal.y * LightPosition.y+ normal.z * LightPosition.z)/(sqrt(normal.x*normal.x+normal.y*normal.y+normal.z*normal.z)* sqrt(LightPosition.x * LightPosition.x + LightPosition.y * LightPosition.y + LightPosition.z * LightPosition.z));
	 Ambient.x = (LightAmbient.x) * ModelAmbient.x;
	 Ambient.y = (LightAmbient.y) * ModelAmbient.y;
	 Ambient.z = (LightAmbient.z) * ModelAmbient.z;

	 Diffuse.x = (LightDiffuse.x) *ModelDiffuse.x;
	 Diffuse.y = (LightDiffuse.y) *ModelDiffuse.y;
	 Diffuse.z = (LightDiffuse.z) *ModelDiffuse.z;
	 Diffuse *= glm::dot(normal,LightPosition);
	 Specular.x = (LightSpecular.x) * ModelSpecular.x;
	 Specular.y = (LightSpecular.y) * ModelSpecular.y;
	 Specular.z = (LightSpecular.z) * ModelSpecular.z;
	 r = 2.f * glm::dot(normal, LightPosition) * normal - LightPosition;
	 float pow = std::pow(std::max(0.f, glm::dot(r, LightPosition)),alpha);
	 Specular *= pow;
	 color= (Ambient + Diffuse + Specular);
	 if (color.x > 1.f)color.x = 1.f;
	 if (color.y > 1.f)color.y = 1.f;
	 if (color.z > 1.f)color.z = 1.f;
	 return color;
 }

void Renderer::Fog(Scene& scene)
 {
	 scene.SetFogBegin(minz );//check
	 scene.SetFogEnd(maxz );
	 glm::vec3 color;
	 for (int i = 0; i < viewport_height_; i++)
		 for (int j = 0; j < viewport_width_; j++)
		 {
			 float z = Z_buffer_[i*viewport_width_+j];
			 if (z != FLT_MAX)
			 {
				 color = glm::vec3(color_buffer_[INDEX(viewport_width_, j, i, 0)], color_buffer_[INDEX(viewport_width_, j, i, 1)], color_buffer_[INDEX(viewport_width_, j, i, 2)]);

				 float vertexViewDistance = z;

				 float fogFactor;

				 if (scene.GetLinearFog())
				 {
					 fogFactor = (scene.GetFogEnd() - vertexViewDistance) / (scene.GetFogEnd() - scene.GetFogBegin());
				 }
				 else
				 {
					 fogFactor = std::exp(-(vertexViewDistance * vertexViewDistance * scene.GetFogDensity() * scene.GetFogDensity()));
					 if (fogFactor < 0 || fogFactor > 1)
						 fogFactor = 1;
				 }
				 color = ((1 - fogFactor) * glm::vec3(0.5, 0.5, 0.5) + fogFactor * color);
				 color_buffer_[INDEX(viewport_width_, j, i, 0)] = color.x;
				 color_buffer_[INDEX(viewport_width_, j, i, 1)] = color.y;
				 color_buffer_[INDEX(viewport_width_, j, i, 2)] = color.z;
			 }
		 }
 }