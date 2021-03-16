#pragma once
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <stdlib.h>

extern char keybEvent[512];
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouseButtonsCallback(GLFWwindow*window, int button, int action, int mods);
