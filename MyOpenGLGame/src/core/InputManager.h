#pragma once

#include <GLFW/glfw3.h>

#include <iostream>
#include <utility>

namespace InputManager {

	class KeyBoard 
	{
	public:
		static bool IsKeyDown(int key)
		{
			return s_Keys[key];
		}

		static void init(GLFWwindow* window)
		{
			if (!s_IsKeyBoardSetUp)
			{
				memset(s_Keys, false, sizeof(s_Keys));

				glfwSetKeyCallback(window, KeyBoard::KeyCallBack);

#ifdef DEBUG
				std::cout << "Keyboard input manager initialized!" << std::endl;
#endif // DEBUG
			
				// change the state of keyboard setup to true
				s_IsKeyBoardSetUp = true;
			}
		}

	private: 
		KeyBoard() = delete;
		KeyBoard(const KeyBoard&) = delete;
		
		static bool s_IsKeyBoardSetUp;
		static bool s_Keys[GLFW_KEY_LAST];


		static void KeyCallBack(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			if (action != GLFW_RELEASE)
			{
				s_Keys[key] = true;
			}
			else
			{
				s_Keys[key] = false;
			}
		}
	};

	class Mouse
	{
	public:
		static bool IsButtonDown(int key)
		{
			return s_Buttons[key];
		}

		static void init(GLFWwindow* window)
		{
			if (!s_IsMouseSetUp)
			{
				memset(s_Buttons, false, sizeof(s_Buttons));

				glfwSetMouseButtonCallback(window, Mouse::MouseCallBack);
#ifdef DEBUG
				std::cout << "Mouse input manager initialized!" << std::endl;
#endif // DEBUG
				// change the state of the mouse set up to true
				s_IsMouseSetUp = true;
			}
		}

	private:
		Mouse() = delete;
		Mouse(const Mouse&) = delete;
		
		static bool s_IsMouseSetUp;
		static bool s_Buttons[GLFW_MOUSE_BUTTON_LAST];

		static void MouseCallBack(GLFWwindow* window, int button, int action, int mods)
		{
			if (action != GLFW_RELEASE)
			{
				s_Buttons[button] = true;
			}
			else
			{
				s_Buttons[button] = false;
			}
		}
	};

	class MouseCursor
	{
	public:
		static double GetMouseXPos()
		{
			return s_XPos;
		}

		static double GetMouseYPos()
		{
			return s_YPos;
		}

		static std::pair<int, int> GetMousePosXY()
		{
			return { s_XPos, s_YPos };
		}
		static void init(GLFWwindow* window)
		{
			if (!s_IsMouseCursorSetUp)
			{
				glfwSetCursorPosCallback(window, MouseCursor::MouseCursorCallBack);
#ifdef DEBUG
				std::cout << "Mouse Cursor input manager initialized!" << std::endl;
#endif // DEBUG
				// change the state of the mouse set up to true
				s_IsMouseCursorSetUp = true;
			}
		}

	private:

		MouseCursor() = delete;
		MouseCursor(const MouseCursor&) = delete;

		static bool s_IsMouseCursorSetUp;
		static double s_XPos, s_YPos;
		
		static void MouseCursorCallBack(GLFWwindow* window, double xPos, double yPos)
		{
			MouseCursor::s_XPos = xPos;
			MouseCursor::s_YPos = yPos;
		}
	};
}