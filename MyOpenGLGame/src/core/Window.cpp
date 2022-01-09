#include "Window.h"
#include "InputManager.h"

#include <iostream>
#include <string>
#include <exception>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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

	// initialize input managers
	InputManager::KeyBoard::init(m_Window);
	InputManager::Mouse::init(m_Window);
	InputManager::MouseCursor::init(m_Window);

	//ImGui initialization

	//ImGUI setup
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(this->m_Window, true);
	ImGui_ImplOpenGL3_Init("#version 430");
}
