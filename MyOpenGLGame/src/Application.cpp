#include <iostream>

#include "core/Window.h"

#include "core/models/Triangle.h"
#include "core/CameraPerspective.h"
#include "core/Texture2D.h"
#include "core/logging/Logger.h"

#include <glm/gtc/type_ptr.hpp>
#include "core/InputManager.h"

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <stb_image/stb_image.h>

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;
	glm::vec2 tc;
};

void* operator new(size_t bytes)
{
	if (bytes < 0)
		return nullptr;
	
	char MSG[1024];
	snprintf(MSG, sizeof(MSG), "Allocating bytes: %u", bytes);
	Logger::log(MSG, Log::WARNING);
	
	return malloc(bytes);
}

void operator delete(void* mem, size_t bytes)
{
	char MSG[1024];
	snprintf(MSG, sizeof(MSG), "De-allocating bytes: %u", bytes);

	Logger::log(MSG, Log::INFO);
	free(mem);
}

void triangleSetUp(std::array<Vertex, 3>& verts, GLuint* vbo);

double mouseXPos, mouseYPos;

// Input processing
void ProcessInput(GLFWwindow* window);

// Window Clear Color
glm::vec4 clearColor = { 1.0f, .0f, .0f, 1.0f };

void zoomCameraIn(Camera* cam);
void zoomCameraOut(Camera* cam);

int main()
{
	Logger::init(Log::INFO, true);
	Window window("My Game", 1280, 720);

	Logger::log("Window Created!");

	Shader vShader(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\src\shaders\crazy_triangle_vert.glsl)", GL_VERTEX_SHADER),
		fShader(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\src\shaders\crazy_triangle_frag.glsl)", GL_FRAGMENT_SHADER);

	Texture2D wallTexture(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\assets\Textures\wall.jpg)", 3, true, true);
	Triangle<Vertex> triangle;
	triangle[0] = { glm::vec2{-0.5, -0.5}, glm::vec3{1.0, 1.0, 0.0}, glm::vec2{0.0, 0.0} };
	triangle[1] = { glm::vec2{0.0, 0.5}  , glm::vec3{0.0, 1.0, 0.0}, glm::vec2{0.5, 1.0} };
	triangle[2] = { glm::vec2{0.5, -0.5} , glm::vec3{1.0, 0.0, 1.0}, glm::vec2{1.0, 0.0} };

	triangle.Model(vShader, fShader, 1, triangleSetUp);
	triangle.FitTexture(&wallTexture);

	int width, height;
	float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 8.0f;
	glfwGetFramebufferSize(window.GetWindowHandle(), &width, &height);
	
	CameraPerspective pCam(glm::vec3(-cameraX, -cameraY, -cameraZ), .1, 100., width, height);

	double mousePrevX = mouseXPos, mousePrevY = mouseYPos;
	double camPosX = {}, camPosY = {};
	
	auto modelMat = glm::translate(glm::mat4(1.0f), 
			glm::vec3(0.0, 0.0, 0.0));

	while (!glfwWindowShouldClose(&window))
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Hello, World");                          // Create a window called "Hello, world!" and append into it.

		ImGui::Text("Change Window Properties");               // Display some text (you can use a format strings too)
		

		ProcessInput(&window);

		auto[mouseXPos, mouseYPos] = InputManager::MouseCursor::GetMousePosXY();
		
		auto delXMouse = mouseXPos - mousePrevX;
		auto delYMouse = mouseYPos - mousePrevY;

		mousePrevX = mouseXPos;		mousePrevY = mouseYPos;

		if (!(abs(delXMouse) <= abs(1e-3)))
		{
			camPosX += (int)delXMouse % 2;
		}
		if (!(abs(delYMouse) <= abs(1e-3)))
		{
			camPosY += (int)delYMouse % 2;
		}

		// Provide sliders to change clear color
		ImGui::SliderFloat4("Clear Color", &clearColor[0], 0.0f, 1.0f);
		ImGui::Text("Choose your window color");

		pCam.rotateByAmtandAxis(0.5f, glm::vec3(0.0, 1.0, 0.0));


		if (InputManager::KeyBoard::IsKeyDown(GLFW_KEY_UP))
		{
			zoomCameraIn(&pCam);
		}
		if (InputManager::KeyBoard::IsKeyDown(GLFW_KEY_DOWN))
		{
			zoomCameraOut(&pCam);
		}

		pCam.translateByAmt(glm::vec3(delXMouse / 1000., delYMouse/ 1000., 0.0f));
		ImGui::End();
		auto resMat = pCam.getProjectionMat() * pCam.getViewMat() * modelMat;
		glClear(GL_COLOR_BUFFER_BIT);

		auto& tSp = triangle.GetRenderingProgram();
		tSp.BindUniform1f(glfwGetTime(), "time");
		tSp.BindUniformMatrix4fv(resMat, "proj");
		triangle.Render();


		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(&window);
		glfwPollEvents();
	}


	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

void triangleSetUp(std::array<Vertex, 3>& verts, GLuint* vbo)
{
	Vertex* vertices = verts.data();
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 21,
		vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		7 * sizeof(float), (const void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		7 * sizeof(float), (const void*)8);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
		7 * sizeof(float), (const void*)20);


	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ProcessInput(GLFWwindow* window)
{
	if (InputManager::KeyBoard::IsKeyDown(GLFW_KEY_Q))
	{
		glfwSetWindowShouldClose(window, true);
	}
}

void zoomCameraIn(Camera* cam)
{
	cam->moveZ(0.5);
}

void zoomCameraOut(Camera* cam)
{
	cam->moveZ(-0.5);
}
