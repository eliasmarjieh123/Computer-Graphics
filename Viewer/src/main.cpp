#define _USE_MATH_DEFINES
#include <cmath>
#include <imgui/imgui.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <nfd.h>
#include <iostream>
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <string>
#include "Renderer.h"
#include "Scene.h"
#include "Utils.h"
#include "Camera.h"
/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
bool show_transformations_window = false;
bool show_camera_transformations_window = false;
bool show_what_to_show_window = false;
bool Draw_Vertex_Normal = false;
bool Draw_Bounding_Box = false;
bool Draw_Face_Normal = false;

glm::vec4 clear_color = glm::vec4(0.8f, 0.8f, 0.8f, 1.00f);

/**
 * Function declarations
 */
static void GlfwErrorCallback(int error, const char* description);
GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name);
ImGuiIO& SetupDearImgui(GLFWwindow* window);
void StartFrame();
void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io);
void Cleanup(GLFWwindow* window);
void DrawImguiMenus(ImGuiIO& io, Scene& scene);

/**
 * Function implementation
 */
void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	ImGui_ImplGlfw_ScrollCallback(window, xoffset, yoffset);
	// TODO: Handle mouse scroll here
}

int main(int argc, char **argv)
{
	int windowWidth = 1920, windowHeight = 1080,i=0;
	GLFWwindow* window = SetupGlfwWindow(windowWidth, windowHeight, "Mesh Viewer");
	if (!window)
		return 1;

	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);

	Renderer renderer = Renderer(frameBufferWidth, frameBufferHeight);
	Scene scene = Scene();
	ImGuiIO& io = SetupDearImgui(window);
	glfwSetScrollCallback(window, ScrollCallback);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
		StartFrame();
		DrawImguiMenus(io, scene);
		RenderFrame(window, scene, renderer, io);
    }

	Cleanup(window);
	renderer.~Renderer();
    return 0;
}

static void GlfwErrorCallback(int error, const char* description)
{
	fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLFWwindow* SetupGlfwWindow(int w, int h, const char* window_name)
{
	glfwSetErrorCallback(GlfwErrorCallback);
	if (!glfwInit())
		return NULL;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	#if __APPLE__
		glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	#endif
	
	GLFWwindow* window = glfwCreateWindow(w, h, window_name, NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync
						 // very importent!! initialization of glad
						 // https://stackoverflow.com/questions/48582444/imgui-with-the-glad-opengl-loader-throws-segmentation-fault-core-dumped

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	return window;
}

ImGuiIO& SetupDearImgui(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init();
	ImGui::StyleColorsDark();
	return io;
}

void StartFrame()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void RenderFrame(GLFWwindow* window, Scene& scene, Renderer& renderer, ImGuiIO& io)
{
	ImGui::Render();
	int frameBufferWidth, frameBufferHeight;
	glfwMakeContextCurrent(window);
	glfwGetFramebufferSize(window, &frameBufferWidth, &frameBufferHeight);
	
	if (frameBufferWidth != renderer.GetViewportWidth() || frameBufferHeight != renderer.GetViewportHeight())
	{
		glfwSetWindowAspectRatio(window,1920,1080);
		// TODO: Set new aspect ratio
	}

	if (!io.WantCaptureKeyboard)
	{
		// TODO: Handle keyboard events here
		if (io.KeysDown[65])
		{
			// A key is down
			// Use the ASCII table for more key codes (https://www.asciitable.com/)
		}
	}

	if (!io.WantCaptureMouse)
	{
		// TODO: Handle mouse events here
		if (io.MouseDown[0])
		{
			// Left mouse button is down
		}
	}

	renderer.ClearColorBuffer(clear_color);
	renderer.Render(scene);
	renderer.SwapBuffers();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	glfwMakeContextCurrent(window);
	glfwSwapBuffers(window);
}

void Cleanup(GLFWwindow* window)
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void DrawImguiMenus(ImGuiIO& io, Scene& scene)
{
	/**
	 * MeshViewer menu
	 */
	ImGui::Begin("MeshViewer Menu");
	
	// Menu Bar
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Open Model", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddModel(Utils::LoadMeshModel(outPath));

					//scene.GetActiveModel().printFacesAndVertices();
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			if (ImGui::MenuItem("Open Camera", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddCamera(Utils::LoadCamera(outPath));
					//scene.GetActiveCamera().printFacesAndVertices();
					free(outPath);
				}
				else if (result == NFD_CANCEL)
				{
				}
				else
				{
				}

			}
			ImGui::EndMenu();
		}

		// TODO: Add more menubar items (if you want to)
		ImGui::EndMainMenuBar();
	}

	// Controls
	ImGui::ColorEdit3("Clear Color", (float*)&clear_color);
	// TODO: Add more controls as needed
	
	ImGui::End();

	/**
	 * Imgui demo - you can remove it once you are familiar with imgui
	 */
	
	// 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
	{
		static float f = 0.0f;
		static int counter = 0;

		ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
		ImGui::Checkbox("Another Window", &show_another_window);
		ImGui::Checkbox("Model Transformations Window", &show_transformations_window);
		ImGui::Checkbox("Model Properties Window", &show_what_to_show_window);
		ImGui::Checkbox("Camera Transformations Window", &show_camera_transformations_window);
		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
		ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

		if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
			counter++;
		ImGui::SameLine();
		ImGui::Text("counter = %d", counter);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::End();
	}

	// 3. Show another simple window.
	static float FOV=70.0f,orthow = 20.f, xscale = 1, yscale = 1, zscale = 1, ztranslate = 0, xtranslate = 0, ytranslate = 0, AnglewX = 0, AnglewY = 0, AnglewZ = 0, AngleX = 0, AngleY = 0, AngleZ = 0, xscalew = 1, yscalew = 1, zscalew = 1, ztranslatew = 0, xtranslatew = 0, ytranslatew = 0;
	static glm::vec3 VertexNormalsColor(0.8f,0.8f,0.8f) ;
	static glm::vec3 FaceNormalsColor(0.8f,0.8f,0.8f) ;
	static glm::vec3 BoundingBoxColor(0.8f,0.8f,0.8f) ;
	static float eye[3] = { 0,0,10 };
	static float at[3] = { 0,0,0 };
	static float up[3] = { 0,1,0 };
	if ( scene.GetCameraCount() > 0) {
		//eye[0]=scene.GetActiveCamera().GetEye().x;
		//eye[1]=scene.GetActiveCamera().GetEye().y;
		//eye[2]=scene.GetActiveCamera().GetEye().z;
		//at[0] = scene.GetActiveCamera().GetAt().x;
		//at[1] = scene.GetActiveCamera().GetAt().y;
		//at[2] = scene.GetActiveCamera().GetAt().z;
		//up[0] = scene.GetActiveCamera().GetUp().x;
		//up[1] = scene.GetActiveCamera().GetUp().y;
		//up[2] = scene.GetActiveCamera().GetUp().z;
	}
	glm::vec3 lastEye = glm::vec3(eye[0], eye[1], eye[2]);
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	if (show_what_to_show_window)
	{
		ImGui::Begin("Show Window", &show_what_to_show_window);
		ImGui::Checkbox("Draw Normal Per Vertex", &Draw_Vertex_Normal);
		ImGui::Checkbox("Draw Normal Per Face", &Draw_Face_Normal);
		ImGui::Checkbox("Draw Bounding Box", &Draw_Bounding_Box);
		if (Draw_Vertex_Normal) {
			scene.GetActiveModel().Set_ShowVertexNormals(1);
			ImGui::ColorEdit3("Pick Vertex Normals Color", (float*)&VertexNormalsColor);
			scene.GetActiveModel().Set_ShowVertexNormalsColor(VertexNormalsColor);
		}
		else {
			scene.GetActiveModel().Set_ShowVertexNormals(0);
		}
		if (Draw_Face_Normal) {
			scene.GetActiveModel().Set_ShowFaceNormals(1);
			ImGui::ColorEdit3("Pick Face Normals Color", (float*)&FaceNormalsColor);
			scene.GetActiveModel().Set_ShowFaceNormalsColor(FaceNormalsColor);
		}
		else {
			scene.GetActiveModel().Set_ShowFaceNormals(0);
		}
		if (Draw_Bounding_Box) {
			scene.GetActiveModel().Set_ShowBoundingBox(1);
			ImGui::ColorEdit3("Pick Bounding Box Color", (float*)&BoundingBoxColor);
			scene.GetActiveModel().Set_ShowBoundingBoxColor(BoundingBoxColor);
		}
		else {
			scene.GetActiveModel().Set_ShowBoundingBox(0);
		}
		ImGui::End();
	}
	if (show_transformations_window)
	{
		ImGui::Begin("Model Transformations Window", &show_transformations_window);
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
		{ 
			if (ImGui::BeginTabItem("Local")) {
				if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
				{
					if (ImGui::BeginTabItem("Scale"))
					{
						ImGui::SliderFloat("Scale by x", &xscale, 0.0f, 3.0f, "%.5f");
						ImGui::SliderFloat("Scale by y", &yscale, 0.0f, 3.0f, "%.5f");
						ImGui::SliderFloat("Scale by z", &zscale, 0.0f, 3.0f, "%.5f");
							scene.GetActiveCamera().ScaleVertices("local", xscale, yscale, zscale);
						if (ImGui::Button("Reset Model"))
						{
							scene.GetActiveCamera().ResetModel();
							xscale = 1;
							yscale = 1;
							zscale = 1;
							xtranslate = 0;
							ytranslate = 0;
							ztranslate = 0;
							xscalew = 1;
							yscalew = 1;
							zscalew = 1;
							xtranslatew = 0;
							ytranslatew = 0;
							ztranslatew = 0;
							AngleX = 0;
							AngleY = 0;
							AngleZ = 0;
							AnglewX = 0;
							AnglewY = 0;
							AnglewZ = 0;
						}
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Translate")) {
						ImGui::SliderFloat("Translate by x", &xtranslate, 0.0f, 700.0f, "%.0f");
						ImGui::SliderFloat("Translate by y", &ytranslate, 0.0f, 700.0f, "%.0f");
						ImGui::SliderFloat("Translate by z", &ztranslate, 0.0f, 700.0f, "%.0f");
						scene.GetActiveCamera().TranslateVertices("local", xtranslate, ytranslate, ztranslate);
						if (ImGui::Button("Reset Model"))
						{
							scene.GetActiveCamera().ResetModel();
							xscale = 1;
							yscale = 1;
							zscale = 1;
							xtranslate = 0;
							ytranslate = 0;
							ztranslate = 0;
							xscalew = 1;
							yscalew = 1;
							zscalew = 1;
							xtranslatew = 0;
							ytranslatew = 0;
							ztranslatew = 0;
							AngleX = 0;
							AngleY = 0;
							AngleZ = 0;
							AnglewX = 0;
							AnglewY = 0;
							AnglewZ = 0;
						}
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Rotate"))
					{
						ImGui::SliderFloat("Angle of Rotation By X", &AngleX, 0.0f, 360.0f, "%.f");
						ImGui::SliderFloat("Angle of Rotation By Y", &AngleY, 0.0f, 360.0f, "%.f");
						ImGui::SliderFloat("Angle of Rotation By Z", &AngleZ, 0.0f, 360.0f, "%.f");
							scene.GetActiveCamera().RotateModel("local", 0, AngleX);
							scene.GetActiveCamera().RotateModel("local", 1, AngleY );
							scene.GetActiveCamera().RotateModel("local", 2, AngleZ );
						if (ImGui::Button("Reset Model"))
						{
							scene.GetActiveCamera().ResetModel();
							xscale = 1;
							yscale = 1;
							zscale = 1;
							xtranslate = 0;
							ytranslate = 0;
							ztranslate = 0;
							xscalew = 1;
							yscalew = 1;
							zscalew = 1;
							xtranslatew = 0;
							ytranslatew = 0;
							ztranslatew = 0;
							AngleX = 0;
							AngleY = 0;
							AngleZ = 0;
							AnglewX = 0;
							AnglewY = 0;
							AnglewZ = 0;
						}
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("World")) {
				if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
				{
					if (ImGui::BeginTabItem("Scale"))
					{
						ImGui::SliderFloat("Scale by x", &xscalew, 0.0f, 3.0f, "%.5f");
						ImGui::SliderFloat("Scale by y", &yscalew, 0.0f, 3.0f, "%.5f");
						ImGui::SliderFloat("Scale by z", &zscalew, 0.0f, 3.0f, "%.5f");
							scene.GetActiveCamera().ScaleVertices("world", xscalew, yscalew, zscalew);
						if (ImGui::Button("Reset Model"))
						{
							scene.GetActiveCamera().ResetModel();
							xscale = 1;
							yscale = 1;
							zscale = 1;
							xtranslate = 0;
							ytranslate = 0;
							ztranslate = 0;
							xscalew = 1;
							yscalew = 1;
							zscalew = 1;
							xtranslatew = 0;
							ytranslatew = 0;
							ztranslatew = 0;
							AngleX = 0;
							AngleY = 0;
							AngleZ = 0;
							AnglewX = 0;
							AnglewY = 0;
							AnglewZ = 0;
						}
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Translate")) {
						ImGui::SliderFloat("Translate by x", &xtranslatew, 0.0f, 700.0f, "%.0f");
						ImGui::SliderFloat("Translate by y", &ytranslatew, 0.0f, 700.0f, "%.0f");
						ImGui::SliderFloat("Translate by z", &ztranslatew, 0.0f, 700.0f, "%.0f");
							scene.GetActiveCamera().TranslateVertices("world", xtranslatew, ytranslatew, ztranslatew);
						if (ImGui::Button("Reset Model"))
						{
							scene.GetActiveCamera().ResetModel();
							xscale = 1;
							yscale = 1;
							zscale = 1;
							xtranslate = 0;
							ytranslate = 0;
							ztranslate = 0;
							xscalew = 1;
							yscalew = 1;
							zscalew = 1;
							xtranslatew = 0;
							ytranslatew = 0;
							ztranslatew = 0;
							AngleX = 0;
							AngleY = 0;
							AngleZ = 0;
							AnglewX = 0;
							AnglewY = 0;
							AnglewZ = 0;
						}
						ImGui::EndTabItem();
					}
					if (ImGui::BeginTabItem("Rotate"))
					{
						ImGui::SliderFloat("Angle of Rotation By X", &AnglewX, 0.0f, 360.0f, "%.f");
						ImGui::SliderFloat("Angle of Rotation By Y", &AnglewY, 0.0f, 360.0f, "%.f");
						ImGui::SliderFloat("Angle of Rotation By Z", &AnglewZ, 0.0f, 360.0f, "%.f");
							scene.GetActiveCamera().RotateModel("world", 0, AnglewX );
							scene.GetActiveCamera().RotateModel("world", 1, AnglewY );
							scene.GetActiveCamera().RotateModel("world", 2, AnglewZ );
						if (ImGui::Button("Reset Model"))
						{
							scene.GetActiveCamera().ResetModel();
							xscale = 1;
							yscale = 1;
							zscale = 1;
							xtranslate = 0;
							ytranslate = 0;
							ztranslate = 0;
							xscalew = 1;
							yscalew = 1;
							zscalew = 1;
							xtranslatew = 0;
							ytranslatew = 0;
							ztranslatew = 0;
							AngleX = 0;
							AngleY = 0;
							AngleZ = 0;
							AnglewX = 0;
							AnglewY = 0;
							AnglewZ = 0;
						}
						ImGui::EndTabItem();
					}
					ImGui::EndTabBar();
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		ImGui::End();
	}
	if (show_camera_transformations_window&&scene.GetCameraCount()>0) {
		ImGui::Begin("Camera Transformations Window", &show_camera_transformations_window);
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
		{
			if (ImGui::BeginTabItem("Orthographic")) {
				ImGui::SliderFloat("Pick Orthographic width", &orthow, 1.f, 20.f);
				scene.GetActiveCamera().SetWidth(orthow);
				scene.GetActiveCamera().SetIfOrthographicProjection(1);
				scene.GetActiveCamera().UpdateProjectionMatrix();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Perspective")) {
				ImGui::SliderFloat("Pick Perspective FOV", &FOV, 20.f, 110.f, "%.f");
				scene.GetActiveCamera().SetIfOrthographicProjection(0);
				scene.GetActiveCamera().SetFOV(FOV);
				scene.GetActiveCamera().UpdateProjectionMatrix();
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
		if (ImGui::InputFloat3("Eye", eye, 3))
		{
			glm::vec3 eyeVec = glm::vec3(eye[0], eye[1], eye[2]);
			scene.GetActiveCamera().SetEye(eyeVec);
			scene.GetActiveCamera().UpdateWorldTransformation(eyeVec - lastEye);
		}

		if (ImGui::InputFloat3("At", at, 3))
		{
			scene.GetActiveCamera().SetAt(glm::vec3(at[0], at[1], at[2]));
		}

		if (ImGui::InputFloat3("Up", up, 3))
		{
			scene.GetActiveCamera().SetUp(glm::vec3(up[0], up[1], up[2]));
		}
		if (ImGui::Button("Look At"))
		{
			scene.GetActiveCamera().SetCameraLookAt(glm::vec3(eye[0],eye[1],eye[2]), glm::vec3(at[0], at[1], at[2]), glm::vec3(up[0], up[1], up[2]));
		}
		   ImGui::End();
	}
}




