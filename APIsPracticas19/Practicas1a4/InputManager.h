#pragma once
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct Mouse {

	double x;
	double y;
	void Print();
};
extern char keyInputs[512];
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
bool isKeyDown(int key);

class InputManager
{
public:
	InputManager(GLFWwindow * currentWindow);
	~InputManager();

	static Mouse GetMousePosition();
	static bool isKeyDown(char key);
private:
	static Mouse mousePosition;
	static GLFWwindow * currentWindow;
};

