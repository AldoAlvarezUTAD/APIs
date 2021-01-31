#include "shaderManager.h"

//vertex shader basico
//vertex -> vertex position
//gl_Position-> la posicion de los vertices ya modificados
//
//MVP->modelo vista proyeccion | se calcula 1 vez para todos los shaders
// Modelo		-> guarda transformaciones, rotaciones, escalados, movimientos
// Vista		-> transformaciones de camara, desde donde miramos
// Proyeccion	-> frustrum, volumen de renderizado | orto perspectiva
const char* vertexShader = "\n\
#version 330\n\
\n\
uniform mat4 MVP;\n\
in vec4 vpos;\n\
in vec2 vtex;\n\
out vec2 ftex;\n\
out vec4 vertexColor;\n\
\n\
void main()\n\
{\n\
\n\
gl_Position=MVP*vpos;\n\
vertexColor=vec4(1.0f,1.0f,1.0f,1.0f);\n\
ftex=vtex;\n\
\n\
}\n\
";


const char* fragmentShader = "\n\
#version 330\n\
\n\
in vec2 ftex;\n\
in vec4 vertexColor;\n\
uniform sampler2D texSampler;\n\
out vec4 fragColor;\n\
\n\
void main()\n\
{\n\
\n\
/*fragColor=vertexColor;*/\n\
gl_FragColor=texture2D(texSampler,ftex);\n\
\n\
}\n\
";

int compileShader(const char*shader, GLenum shaderType) 
{
	int shaderID = glCreateShader(shaderType);
	//setea el codigo fuente en el compilador y entrelazarlo con
	// el identificador shaderID
	glShaderSource(shaderID, 1, &shader, nullptr);
	glCompileShader(shaderID);
	checkShaderError(shaderID);
	return shaderID;
}

int compileAndLinkShader(const char*vertexShader, const char*fragmentShader) 
{
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
