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

/**
 * Fields
 */
bool show_demo_window = false;
bool show_another_window = false;
bool show_transformations_window = false;
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
	int windowWidth = 1280, windowHeight = 720,i=0;
	char * path= "C:\\Users\\elias\\OneDrive\\Documents\\GitHub\\computergraphics2021-eliass\\Data\\banana.obj";
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
			if (ImGui::MenuItem("Open", "CTRL+O"))
			{
				nfdchar_t* outPath = NULL;
				nfdresult_t result = NFD_OpenDialog("obj;", NULL, &outPath);
				if (result == NFD_OKAY)
				{
					scene.AddModel(Utils::LoadMeshModel(outPath));
					scene.GetActiveModel().ScaleVertices();
					scene.GetActiveModel().TranslateVertices();
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
		ImGui::Checkbox("Transformations Window", &show_transformations_window);
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
	static float xscale = 1, yscale = 1,xtranslate = 0, ytranslate = 0,Angle=0;
	if (show_another_window)
	{
		ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		if (ImGui::Button("Close Me"))
			show_another_window = false;
		ImGui::End();
	}
	if (show_transformations_window)
	{
		ImGui::Begin("Transformations Window", &show_transformations_window);
		if (ImGui::Button("Close Me"))
			show_transformations_window = false;
		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
		{
			if (ImGui::BeginTabItem("Scale"))
			{
				ImGui::SliderFloat("Scale by x", &xscale, 0.0f, 3.0f, "%.5f");

				ImGui::SliderFloat("Scale by y", &yscale, 0.0f, 3.0f, "%.5f");
				if (ImGui::Button("Scale"))
				{
					scene.GetActiveModel().ScaleVertices(0, xscale, yscale, 0);
				}
				if (ImGui::Button("Reset Model"))
				{
					scene.GetActiveModel().ScaleVertices(0, 1, 1, 0);
					scene.GetActiveModel().TranslateVertices(0, 0, 0, 0);
					scene.GetActiveModel().RotateModel(0, 2, 0);
					scene.GetActiveModel().RotateModel(0, 1, 0);
					scene.GetActiveModel().RotateModel(0, 0, 0);
					xscale = 1;
					yscale = 1;
					xtranslate = 0;
					ytranslate = 0;
					Angle = 0;
				}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Translate")){
			ImGui::SliderFloat("Translate by x", &xtranslate, 0.0f, 500.0f, "%.0f");
			ImGui::SliderFloat("Translate by y", &ytranslate, 0.0f, 500.0f, "%.0f");
			if (ImGui::Button("Translate"))
			{
				scene.GetActiveModel().TranslateVertices(0, xtranslate, ytranslate, 0);
			}
			if (ImGui::Button("Reset Model"))
			{
				scene.GetActiveModel().ScaleVertices(0, 1, 1, 0);
				scene.GetActiveModel().TranslateVertices(0, 0, 0, 0);
				scene.GetActiveModel().RotateModel(0, 2, 0);
				scene.GetActiveModel().RotateModel(0, 1, 0);
				scene.GetActiveModel().RotateModel(0, 0, 0);
				xscale = 1;
				yscale = 1;
				xtranslate = 0;
				ytranslate = 0;
				Angle = 0;
			}
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Rotate"))
			{
				ImGui::SliderFloat("Angle of Rotation", &Angle, 0.0f, 6.28319f, "%.5f");
				if (ImGui::Button("Rotate By X axis"))
				{
					scene.GetActiveModel().RotateModel(0,0, Angle);
				}
				if (ImGui::Button("Rotate By Y axis"))
				{
					scene.GetActiveModel().RotateModel(0,1, Angle);
				}
				if (ImGui::Button("Rotate By Z axis"))
				{
					scene.GetActiveModel().RotateModel(0,2, Angle);
				}
				if (ImGui::Button("Reset Model"))
				{
					scene.GetActiveModel().ScaleVertices(0, 1, 1, 0);
					scene.GetActiveModel().TranslateVertices(0, 0, 0, 0);
					scene.GetActiveModel().RotateModel(0,2, 0);
					scene.GetActiveModel().RotateModel(0,1, 0);
					scene.GetActiveModel().RotateModel(0,0, 0);
					xscale = 1;
					yscale = 1;
					xtranslate = 0;
					ytranslate = 0;
					Angle = 0;
				}
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	
		ImGui::End();
	}
}




