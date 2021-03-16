#include "InputManager.h"
#include <iostream>
//#include "State.h"

Mouse InputManager::mousePosition = Mouse{0,0};
GLFWwindow* InputManager::currentWindow = NULL;;
char keyInputs[512];

InputManager::InputManager(GLFWwindow * window)
{
	currentWindow = window;
	//glfwSetCursorPos(currentWindow, State::WindowSize.x/2.0f , State::WindowSize.y / 2.0f);
	//glfwSetCursorPos(currentWindow, 300 , 200);
}


InputManager::~InputManager()
{
}

Mouse InputManager::GetMousePosition()
{
	glfwGetCursorPos(currentWindow, &mousePosition.x, &mousePosition.y);
	return mousePosition;
}

void KeyCallback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		keyInputs[key] = 1;
		break;
	case GLFW_RELEASE:
		keyInputs[key] = 0;
		break;
	default:
		break;
	}
}

bool isKeyDown(int key)
{
	return keyInputs[key];
}


void Mouse::Print()
{
	std::cout << "mouse X: " << x << " | mouse Y: " << y << std::endl;
}
