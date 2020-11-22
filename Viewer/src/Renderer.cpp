#define _USE_MATH_DEFINES
#include <cmath>
#include <algorithm>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/normal.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
	float a,c, e = -(p2.x - p1.x);
	int x = p1.x, y = p1.y;
	//std::cout << p2.y-p1.y  <<"  "<< p2.x-p1.x<<std::endl;

	a = float(float(p2.y - p1.y) / float(p2.x - p1.x));
	//std::cout << a;
	//std::cout << a<<std::endl;
	if (a > 0 && a <= 1) {
			c = p1.y + a * p1.x;
			while (x <= p2.x) {
				//std::cout << e << std::endl;
				//e = 2 * (p2.y - p1.y) * x + 2 * (p2.x - p1.x) * c - 2 * (p2.x - p1.x) * y - (p2.x - p1.x);
				if (e > 0) {
					y++;
					e = e - 2 * (p2.x - p1.x);
				}
				PutPixel(x, y, color);
				x++;
				e = e + 2 * (p2.y - p1.y);
			}
		}

	else if (a >1) {
		int temp = y;
		y = x;
		x = temp;
		c = p1.x + a * p1.y;
		while (x <= p2.y) {
			//std::cout << e << std::endl;
			//e = 2 * (p2.y - p1.y) * x + 2 * (p2.x - p1.x) * c - 2 * (p2.x - p1.x) * y - (p2.x - p1.x);
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
			//std::cout << e << std::endl;
			//e = 2 * (p2.y - p1.y) * x + 2 * (p2.x - p1.x) * c - 2 * (p2.x - p1.x) * y - (p2.x - p1.x);
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
			//std::cout << e << std::endl;
			//e = 2 * (p2.y - p1.y) * x + 2 * (p2.x - p1.x) * c - 2 * (p2.x - p1.x) * y - (p2.x - p1.x);
			if (e > 0) {
				y++;
				e = e + 2 * (p2.y - p1.y);
			}
			PutPixel(y, x, color);
			x--;
			e = e + 2 * (p2.x - p1.x);
		}

	}
	// TODO: Implement bresenham algorithm
	// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
}

void Renderer::CreateBuffers(int w, int h)
{
	CreateOpenGLBuffer(); //Do not remove this line.
	color_buffer_ = new float[3 * w * h];
	ClearColorBuffer(glm::vec3(0.0f, 0.0f, 0.0f));
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

void Renderer::Render(const Scene& scene)
{
	// TODO: Replace this code with real scene rendering code
	int half_width = viewport_width_ / 2;
	int half_height = viewport_height_ / 2;
	int thickness = 15;
	int r = 100, steps = 50;
	float angle = 2.f * PI / steps;
	if (scene.GetModelCount() > 0) {
		auto mesh = &scene.GetActiveModel();
		//for (int i = 0; i < mesh->GetFacesCount(); i++) {
		//	glm::vec3 v1= mesh->GetCenter(i),v4= mesh->GetNormal(i);
		//	glm::ivec2 point1 = glm::ivec2(v1[0], v1[1]);
		//	glm::ivec2 point4 = glm::ivec2(v4[0], v4[1]);
		//	if (point1.x > point4.x) {
		//		DrawLine(point4, point1, glm::vec3(0, 0, 255));
		//	}
		//	else {
		//		DrawLine(point1, point4, glm::vec3(0, 0, 255));
		//	}
		//}
		for (int i = 0; i < mesh->GetFacesCount(); i++) {
			int p1 = mesh->GetFace(i).GetVertexIndex(0);
			int p2 = mesh->GetFace(i).GetVertexIndex(1);
			int p3 = mesh->GetFace(i).GetVertexIndex(2);
			glm::vec3 v1 = mesh->GetVertex(p1 - 1), v2 = mesh->GetVertex(p2 - 1), v3 = mesh->GetVertex(p3 - 1), v4 = mesh->GetNormal(i);
			glm::ivec2 point1 = glm::ivec2(v1[0], v1[1]);
			glm::ivec2 point2 = glm::ivec2(v2[0], v2[1]);
			glm::ivec2 point3 = glm::ivec2(v3[0], v3[1]);
			if (point2.x > point1.x) {
				DrawLine(point1, point2, glm::vec3(0, 0, 0));
			}
			else {
				DrawLine(point2, point1, glm::vec3(0, 0, 0));
			}
			if (point3.x > point1.x) {
				DrawLine(point1, point3, glm::vec3(0, 0, 0));
			}
			else {
				DrawLine(point3, point1, glm::vec3(0, 0, 0));
			}
			if (point2.x > point3.x) {
				DrawLine(point3, point2, glm::vec3(0, 0, 0));
			}
			else {
				DrawLine(point2, point3, glm::vec3(0, 0, 0));
			}
		}
		glm::ivec2 point1 = glm::ivec2(mesh->GetVOfBoundingBox(0).x, mesh->GetVOfBoundingBox(0).y);
		glm::ivec2 point2 = glm::ivec2(mesh->GetVOfBoundingBox(1).x, mesh->GetVOfBoundingBox(1).y);
		glm::ivec2 point3 = glm::ivec2(mesh->GetVOfBoundingBox(2).x, mesh->GetVOfBoundingBox(2).y);
		glm::ivec2 point4 = glm::ivec2(mesh->GetVOfBoundingBox(3).x, mesh->GetVOfBoundingBox(3).y);
		if (point2.x > point1.x) {
			DrawLine(point1, point2, glm::vec3(100, 100, 0));
		}										  
		else {									  
			DrawLine(point2, point1, glm::vec3(100, 100, 0));
		}										 
		if (point3.x > point1.x) {				 
			DrawLine(point1, point3, glm::vec3(100, 100, 0));
		}										 
		else {									 
			DrawLine(point3, point1, glm::vec3(100, 100, 0));
		}										 
		if (point2.x > point4.x) {				 
			DrawLine(point4, point2, glm::vec3(100, 100, 0));
		}										 
		else {									 
			DrawLine(point2, point4, glm::vec3(100, 100, 0));
		}										 
		if (point4.x > point3.x) {				 
			DrawLine(point3, point4, glm::vec3(100, 100, 0));
		}										 
		else {									 
			DrawLine(point4, point3, glm::vec3(100, 100, 0));
		}
		for (int i = 0; i < mesh->GetFacesCount(); i++) {
			Face face= mesh->GetFace(i);
			int vi1 = face.GetVertexIndex(0);
			int vi2 = face.GetVertexIndex(1);
			int vi3 = face.GetVertexIndex(2);
			int vni1 = face.GetNormalIndex(0);
			int vni2 = face.GetNormalIndex(1);
			int vni3 = face.GetNormalIndex(2);
			glm::vec4 v1 = glm::vec4(mesh->GetVertex(vi1 - 1), 1);
			glm::vec4 v2 = glm::vec4(mesh->GetVertex(vi2 - 1), 1);
			glm::vec4 v3 = glm::vec4(mesh->GetVertex(vi3 - 1), 1);
			glm::vec4 vn1 = glm::vec4(mesh->GetVertexNormal(vni1 - 1), 1);
			glm::vec4 vn2 = glm::vec4(mesh->GetVertexNormal(vni2 - 1), 1);
			glm::vec4 vn3 = glm::vec4(mesh->GetVertexNormal(vni3 - 1), 1);
			if ((v1.x / v1.w) < (vn1.x / vn1.w + v1.x)) {
				DrawLine(glm::ivec2(v1.x / v1.w, v1.y / v1.w), glm::ivec2((vn1.x / vn1.w) + v1.x, (vn1.y / vn1.w) + v1.y), glm::vec3(0, 0, 255));
			}
			else {
				DrawLine( glm::ivec2((vn1.x / vn1.w) + v1.x, (vn1.y / vn1.w) + v1.y), glm::ivec2(v1.x / v1.w, v1.y / v1.w), glm::vec3(0, 0, 255));
			}
			if ((v2.x / v2.w )< (vn2.x / vn2.w + v2.x)) {
				DrawLine(glm::ivec2(v2.x / v2.w, v2.y / v2.w), glm::ivec2((vn2.x / vn2.w) + v2.x, (vn2.y / vn2.w) + v2.y), glm::vec3(0, 0, 255));
			}
			else {
				DrawLine(glm::ivec2((vn2.x / vn2.w) + v2.x, (vn2.y / vn2.w) + v2.y), glm::ivec2(v2.x / v2.w, v2.y / v2.w), glm::vec3(0, 0, 255));
			}
			if ((v3.x / v3.w) < (vn3.x / vn3.w + v3.x)) {
				DrawLine(glm::ivec2(v3.x / v3.w, v3.y / v3.w), glm::ivec2((vn3.x / vn3.w) + v3.x, (vn3.y / vn3.w) + v3.y), glm::vec3(0, 0, 255));
			}
			else {
				DrawLine(glm::ivec2((vn3.x / vn3.w) + v3.x, (vn3.y / vn3.w) + v3.y), glm::ivec2(v3.x / v3.w, v3.y / v3.w), glm::vec3(0, 0, 255));
			}
		}
		//for (int i = 0; i < mesh->GetFacesCount(); i++) {
		//	int n1 = mesh->GetFace(i).GetNormalIndex(0);
		//	int n2 = mesh->GetFace(i).GetNormalIndex(1);
		//	int n3 = mesh->GetFace(i).GetNormalIndex(2);
		//	glm::vec3 vn1 = mesh->GetVertexNormal(n1 - 1), vn2 = mesh->GetVertexNormal(n2 - 1), vn3 = mesh->GetVertexNormal(n3 - 1);
		//	glm::ivec2 point111 = glm::ivec2(vn1[0], vn1[1]);
		//	glm::ivec2 point222 = glm::ivec2(vn2[0], vn2[1]);
		//	glm::ivec2 point333 = glm::ivec2(vn3[0], vn3[1]);
		//	int p1 = mesh->GetFace(i).GetVertexIndex(0);
		//	int p2 = mesh->GetFace(i).GetVertexIndex(1);
		//	int p3 = mesh->GetFace(i).GetVertexIndex(2);
		//	glm::vec3 v1 = mesh->GetVertex(p1 - 1), v2 = mesh->GetVertex(p2 - 1), v3 = mesh->GetVertex(p3 - 1);
		//	glm::ivec2 point11 = glm::ivec2(v1[0], v1[1]);
		//	glm::ivec2 point22 = glm::ivec2(v2[0], v2[1]);
		//	glm::ivec2 point33 = glm::ivec2(v3[0], v3[1]);
		//	if (point11.x > point111.x) {
		//		DrawLine(point111, point11, glm::vec3(0, 0, 255));
		//	}
		//	else {
		//		DrawLine(point11, point111, glm::vec3(0, 0, 255));
		//	}
		//	if (point22.x > point222.x) {
		//		DrawLine(point222, point22, glm::vec3(0, 0, 255));
		//	}
		//	else {
		//		DrawLine(point22, point222, glm::vec3(0, 0, 255));
		//	}
		//	if (point333.x > point33.x) {
		//		DrawLine(point33, point333, glm::vec3(0, 0, 255));
		//	}
		//	else {
		//		DrawLine(point333, point33, glm::vec3(0, 0, 255));
		//	}
	    //}
	}
    ///////////////////////////////this loop test Bresenham's algorithm
	//for (int i = 0; i <= steps; i++) {
	//	glm::ivec2 point2 = glm::ivec2(point1.x + r * sin(angle * i), point1.y + r * cos(angle * i));
	//	if (point2.x > point1.x) {
	//		DrawLine(point1, point2, glm::vec3(0, 0, 0));
	//	}
	//	else {
	//		DrawLine(point2, point1, glm::vec3(0, 0, 0));
	//	}
	//}

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