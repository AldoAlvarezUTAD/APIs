#include "GLSLShader.h"
#include <glm/gtx/transform.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include "State.h"

GLSLShader::GLSLShader(const char* vertexShader, const char* fragmentShader)
{
	programID = glCreateProgram();
	int vertexID = CompileShader(vertexShader, GL_VERTEX_SHADER);
	int fragmentID = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);

	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);
}

const char * GLSLShader::GetError()
{
	GLint success = 1;
	char* infoLog = new char[1024];
	glGetShaderiv(programID, GL_COMPILE_STATUS, &success);
	if (!success)
		glGetShaderInfoLog(programID, 1024, nullptr, infoLog);
	return infoLog;
}

void GLSLShader::Use()
{
	glUseProgram(programID);
}

void GLSLShader::SetupAttributes()
{
	int vertexArray = GetAttributeLocation("vpos");
	int uniformMVP = GetUniformLocation("MVP");

	glEnableVertexAttribArray(vertexArray);
	glVertexAttribPointer(vertexArray, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), nullptr);

	glm::mat4 MVP = State::GetMVP();
	glUniformMatrix4fv(uniformMVP, 1, GL_FALSE, &MVP[0][0]);
}

int GLSLShader::GetUniformLocation(const char* name)
{
	return glGetUniformLocation(programID, &name[0]);
}

int GLSLShader::GetAttributeLocation(const char* attribute)
{
	return glGetAttribLocation(programID, &attribute[0]);
}

void GLSLShader::SetInt(int loc, int val)
{
	glUniform1i(loc, val);
}

void GLSLShader::SetFloat(int loc, float val)
{
	glUniform1f(loc, val);
}

void GLSLShader::SetVec3(int loc, glm::vec3 vec)
{
	glUniform3f(loc, vec.x, vec.y, vec.z);
}

void GLSLShader::SetVec4(int loc, glm::vec4 vec)
{
	glUniform4f(loc, vec.x, vec.y, vec.z, vec.w);
}

void GLSLShader::SetMatrix(int loc, glm::mat4 matrix)
{
	glUniformMatrix4fv(loc, 1, GL_FALSE, &matrix[0][0]);
}

int GLSLShader::CompileShader(const char* shader, GLenum shaderType)
{
	int shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &shader, nullptr);
	glCompileShader(shaderID);
	return shaderID;
}