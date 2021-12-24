#include <iostream>

#include "core/Window.h"

#include "core/models/Triangle.h"

#include <glm/gtc/type_ptr.hpp>

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;
};

void triangleSetUp(std::array<Vertex, 3>& verts, GLuint* vbo);

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


	glm::vec2 vertices[] = {
		{-0.5, -0.5},
		{0.0, 0.5},
		{0.5, -0.5}
	};


	while (!glfwWindowShouldClose(window.GetWindowHandle()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		auto& tSp = triangle.GetRenderingProgram();
		tSp.BindUniform1f(glfwGetTime(), "time");
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