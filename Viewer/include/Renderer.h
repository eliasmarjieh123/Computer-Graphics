#pragma once
#include "Scene.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class Renderer
{
public:
	Renderer(int viewportWidth, int viewportHeight);
	virtual ~Renderer();
	void Render( Scene& scene);
	void SwapBuffers();
	void ClearColorBuffer(const glm::vec3& color);
	int GetViewportWidth() const;
	int GetViewportHeight() const;
	glm::mat4x4 Renderer::GetViewPortTransformation();
	void DrawFaces(glm::mat4x4 Transformation, MeshModel& mesh);
	void DrawVertexNormals(glm::mat4x4 Transformation, MeshModel& mesh);
	void DrawFaceNormals(glm::mat4x4 Transformation, MeshModel& mesh);
	void DrawBoundingBox(Camera& mesh);
	void Renderer::DrawFaces2(glm::mat4x4 Transformation, glm::mat4x4 view, MeshModel& mesh, bool ortho, Scene& s,glm::vec3 v);
	void FillTriangle(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, int i,glm::mat4x4 t, MeshModel& mesh,glm::vec3 v, Scene& s);
	bool PointInTriangle(int x, int y);
	bool CheckIfLastFaceFromRight(int x, int y, int maxx);
	void ClearZbuffer(int w, int h);
	glm::vec3 CalculateZ(glm::vec3 p, glm::vec3 v1, glm::vec3 v2, glm::vec3 v3, glm::vec3 val1, glm::vec3 val2, glm::vec3 val3);
	void ZBufferGrayscale();
	float CalcArea(glm::vec3 v1, glm::vec3 v2, glm::vec3 v3);
	bool PointInTriangle(glm::vec3 p, glm::vec3 p0, glm::vec3 p1, glm::vec3 p2);
	glm::vec3 CalculateColor(int a,glm::vec3 normal, glm::vec3 LightPosition, glm::vec3 ModelAmbient, glm::vec3 ModelDiffuse, glm::vec3 ModelSpecular, glm::vec3 LightAmbient, glm::vec3 LightDiffuse, glm::vec3 LightSpecular,glm::vec3 v);
	void Fog(Scene& scene);

private:
	void PutPixel(const int i, const int j, const glm::vec3& color);
	void DrawLine(const glm::ivec2& p1, const glm::ivec2& p2, const glm::vec3& color);
	void CreateBuffers(int w, int h);
	void CreateOpenGLBuffer();
	void InitOpenGLRendering();

	float* color_buffer_;
	float* Z_buffer_;
	int viewport_width_;
	int viewport_height_;
	GLuint gl_screen_tex_;
	GLuint gl_screen_vtc_;
	float minz;
	float maxz;
};
