#include "shaderManager.h"

int defaultShaderID = 0;

int compileShader(const char* shader, GLenum shaderType)
{
	int shaderID = glCreateShader(shaderType);
	//setea el codigo fuente en el compilador y entrelazarlo con
	// el identificador shaderID
	glShaderSource(shaderID, 1, &shader, nullptr);
	glCompileShader(shaderID);
	checkShaderError(shaderID);
	return shaderID;
}

int compileAndLinkShader(const char* vertexShaderFile, const char* fragmentShaderFile)
{
	char* vertexShader = readFile(vertexShaderFile);
	char* fragmentShader = readFile(fragmentShaderFile);

	int programID, vertexID, fragmentID;
	//empieza a hablar con la tarjeta grafica para reservar espacio
	//para el codigo que le voy a pasar
	programID = glCreateProgram();
	vertexID = compileShader(vertexShader, GL_VERTEX_SHADER);
	fragmentID = compileShader(fragmentShader, GL_FRAGMENT_SHADER);


	glAttachShader(programID, vertexID);
	glAttachShader(programID, fragmentID);
	glLinkProgram(programID);

	glDetachShader(programID, vertexID);
	glDetachShader(programID, fragmentID);

	//ya linke el programa asi que puedo liberar la memoria
	glDeleteShader(vertexID);
	glDeleteShader(fragmentID);

	return programID;
}

GLint checkShaderError(GLint shaderID)
{
	GLint success = 1;
	char* infoLog = new char[1024];
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
		printf("Error en shader\n%s\n", infoLog);
	}
	return success;
}


char* readFile(const char* fileName)
{
	char* contents = NULL;
	//readonly -> "r"
	FILE* file;
	fopen_s(&file, fileName, "r");
	if (file == NULL)
		return NULL;

	int fileLen = 0;
	fseek(file, 0, SEEK_END);
	fileLen = ftell(file);

	fseek(file, 0, SEEK_SET);
	contents = new char[fileLen + 1];

	fread(contents, 1, fileLen, file);
	contents[fileLen] = '\0';
	fclose(file);
	return contents;
}