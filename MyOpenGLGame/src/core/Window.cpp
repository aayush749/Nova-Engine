#include "Window.h"

#include <iostream>
#include <string>
#include <exception>

Window::Window(const char* title, int width, int height)
	:m_Title(title), m_Width(width), m_Height(height)
{
	if (!glfwInit())
	{
		throw std::exception("GLFW initialization failed");
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);

	if (m_Window == NULL)
	{
		throw std::exception("Window creation failed");
	}

	glfwMakeContextCurrent(m_Window);

	int glewInitStatus;
	if ((glewInitStatus = glewInit()) != GLEW_OK)
	{
		throw std::exception(
			("GLEW initialization failed! Error Code: " + 
			std::to_string(glewInitStatus) + "Description: " 
			+ (const char*)glewGetErrorString(glewInitStatus)).c_str()
		);
	}

	glfwSwapInterval(1);

	std::cout << "Window Created. Current Context Details: " << glGetString(GL_VERSION) << std::endl;
}
