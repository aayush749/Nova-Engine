#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* m_Window;
	const char* m_Title;
	int m_Width, m_Height;

public:
	Window(const char* title, int width, int height);

	GLFWwindow* GetWindowHandle() const 
	{
		return m_Window;
	}

	~Window()
	{
		glfwDestroyWindow(m_Window);
	}
};

