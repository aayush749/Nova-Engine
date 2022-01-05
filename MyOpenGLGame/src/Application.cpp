#include <iostream>

#include "core/Window.h"

#include "core/models/Triangle.h"
#include "core/Camera.h"

#include <glm/gtc/type_ptr.hpp>
#include "core/InputManager.h"

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;
};

void* operator new(size_t bytes)
{
	std::cout << "Allocating " << bytes << " bytes\n";
	return malloc(bytes);
}

void operator delete(void* mem, size_t bytes)
{
	std::cout << "De-allocating " << bytes << " bytes\n";
	free(mem);
}

void triangleSetUp(std::array<Vertex, 3>& verts, GLuint* vbo);

double mouseXPos, mouseYPos;

int main()
{
	Window window("My Game", 1280, 720);

	glClearColor(1.0f, .0f, .0f, 1.0f);
	
	Shader vShader(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\src\shaders\crazy_triangle_vert.glsl)", GL_VERTEX_SHADER),
		fShader(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\src\shaders\crazy_triangle_frag.glsl)", GL_FRAGMENT_SHADER);



	Triangle<Vertex> triangle;
	triangle[0] = { glm::vec2{-0.5, -0.5}, glm::vec3{1.0, 1.0, 0.0} };
	triangle[1] = { glm::vec2{0.0, 0.5}  , glm::vec3{0.0, 1.0, 0.0} };
	triangle[2] = { glm::vec2{0.5, -0.5} , glm::vec3{1.0, 0.0, 1.0} };

	triangle.Model(vShader, fShader, 1, triangleSetUp);

	int width, height;
	float cameraX = 0.0f, cameraY = 0.0f, cameraZ = 8.0f;
	glfwGetFramebufferSize(window.GetWindowHandle(), &width, &height);
	
	Camera camera(glm::vec3(-cameraX, -cameraY, -cameraZ), .1, 100., width, height);

	double mousePrevX = mouseXPos, mousePrevY = mouseYPos;
	double camPosX = {}, camPosY = {};
	
	auto modelMat = glm::translate(glm::mat4(1.0f), 
			glm::vec3(0.0, 0.0, 0.0));

	while (!glfwWindowShouldClose(&window))
	{
		if (InputManager::KeyBoard::IsKeyDown(GLFW_KEY_Q))
		{
			glfwSetWindowShouldClose(&window, true);
		}

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

		camera.rotateByAmtandAxis(0.5f, glm::vec3(0.0, 1.0, 0.0));
		camera.translateByAmt(glm::vec3(delXMouse / 1000., delYMouse/ 1000., 0.0f));

		auto&& resMat = camera.getProjectionMat() * camera.getViewMat() * modelMat;
		glClear(GL_COLOR_BUFFER_BIT);

		auto& tSp = triangle.GetRenderingProgram();
		tSp.BindUniform1f(glfwGetTime(), "time");
		tSp.BindUniformMatrix4fv(resMat, "proj");
		triangle.Render();


		glfwSwapBuffers(window.GetWindowHandle());
		glfwPollEvents();
	}

	glfwTerminate();
}

void triangleSetUp(std::array<Vertex, 3>& verts, GLuint* vbo)
{
	Vertex* vertices = verts.data();
	glGenBuffers(1, vbo);
	glBindBuffer(GL_ARRAY_BUFFER, *vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15,
		vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (const void*)0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
		5 * sizeof(float), (const void*)8);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}