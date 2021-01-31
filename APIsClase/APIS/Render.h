#pragma once
#include "Object.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "camera.h"


//buffer objects ids
struct boIDS 
{
	unsigned int id;
	unsigned int vbo;
	unsigned int idxbo;
};

void UploadObject(Object* obj);
void DeleteObject(Object*obj);
void DrawObject(Object* obj, int shader, camera * cam);
