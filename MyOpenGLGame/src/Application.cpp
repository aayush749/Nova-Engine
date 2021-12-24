#include <iostream>

#include "core/Window.h"

#include "core/models/Triangle.h"

#include <glm/gtc/type_ptr.hpp>

int main()
{
	Window window("My Game", 1280, 720);

	glClearColor(1.0f, .0f, .0f, 1.0f);

	
	Shader vShader(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\src\shaders\triangle_vert.glsl)", GL_VERTEX_SHADER),
		fShader(R"(C:\Users\ANAND\source\repos\MyOpenGLGame\MyOpenGLGame\src\shaders\triangle_frag.glsl)", GL_FRAGMENT_SHADER);


	Triangle triangle;
	triangle[0] = { -0.5, -0.5 };
	triangle[1] = { 0.0, 0.5 };
	triangle[2] = { 0.5, -0.5 };

	triangle.Model(vShader, fShader, 1, [](std::array<glm::vec2, 3>& verts, GLuint* vbo)
		{
			float* vertices = glm::value_ptr(verts[0]);
			glGenBuffers(1, vbo);
			glBindBuffer(GL_ARRAY_BUFFER, *vbo);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6,
				vertices, GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
				2 * sizeof(float), (const void*)0);
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		});


	glm::vec2 vertices[] = {
		{-0.5, -0.5},
		{0.0, 0.5},
		{0.5, -0.5}
	};


	while (!glfwWindowShouldClose(window.GetWindowHandle()))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		triangle.Render();


		glfwSwapBuffers(window.GetWindowHandle());
		glfwPollEvents();
	}

	glfwTerminate();
}