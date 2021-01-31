#pragma once
#include "Render.h"

extern const char*vertexShader;
extern const char*fragmentShader;

int compileShader(const char*shader, GLenum shaderType);
int compileAndLinkShader(const char*vertexShader, const char*fragmentShader);
GLint checkShaderError(GLint shaderID);
