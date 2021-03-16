#include "eventManager.h"

char keybEvent[512];

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		//printf("Tecla presionada %d\n", key);
		keybEvent[key] = 1;
		break;
	case GLFW_RELEASE:
		//printf("Tecla liberada %d\n", key);
		keybEvent[key] = 0;
		break;
	default:
		break;
	}
}

void mouseButtonsCallback(GLFWwindow* window, int button, int action, int mods)
{
	switch (action)
	{
	case GLFW_PRESS:
		break;
	case GLFW_RELEASE:
		break;
	default:
		break;
	}
}