#pragma once
//los includes son para poder cargar la textura a opengl
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
struct Texture
{
	unsigned int textID;
	int width;
	int height;
};

Texture* CreateTexture(const char* fileName);