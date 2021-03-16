#pragma once
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <map>
#include "Vertex.h"
class GLSLShader
{
public:
	GLSLShader(const char* vertexShader, const char* fragmentShader);

	int programID;
	std::map<const char*,int> ShaderAttributes;

	const char* GetError();
	void Use();
	void SetupAttributes();

	int GetUniformLocation(const char* name);
	int GetAttributeLocation(const char* attribute);

	void SetInt(int loc, int val);
	void SetFloat(int loc, float val);
	void SetVec3(int loc, glm::vec3 vec);
	void SetVec4(int loc, glm::vec4 vec);
	void SetMatrix(int loc, glm::mat4 matrix);

private:

	enum AttributeTypes {Int, Float, Vec3, Vec4,Matrix};

	int CompileShader(const char* shader, GLenum shaderType);
};
