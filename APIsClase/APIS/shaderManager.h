#pragma once
#include "Render.h"

//extern const char*vertexShader;
//extern const char*fragmentShader;
extern int defaultShaderID;


int compileShader(const char*shader, GLenum shaderType);
int compileAndLinkShader(const char*vertexShaderFile, const char*fragmentShaderFile);
GLint checkShaderError(GLint shaderID);

char* readFile(const char* fileName);
