#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "Render.h"
#include "eventManager.h"
#include "shaderManager.h"
#include <cstring>
#include <glm/glm.hpp>
#include "camera.h"



int main(int argc, char** argv)
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(600, 400, "APIS 3D", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	//asigno el listener de teclado
	glfwSetKeyCallback(window, keyCallback);


	glewInit();

	glEnable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 1);

	//creo shader
	defaultShaderID = compileAndLinkShader("data/vertexShader.txt", "data/fragmentShader.txt");

	camera* cam = CreateCamera(glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));

	light* l = createLight(DIR_LIGHT,
		glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 1.0f,1.0f));


	//Object* triangle = CreateTriangle();
	//Object* cube = CreateObjectFromFile("data/cube.msh");
	Object* cube = CreateObjectFromFile("data/lightCube.msh");
	//Object* cube = CreateObjectFromFile("data/asian_town.msh");

	//lo llevo a la tarjeta grafica
	UploadObject(cube);


	//SetShaderID(triangle, shaderID);

	while (!glfwWindowShouldClose(window))
	{
		moveCamera(cam);
		MoveObject(cube);

		//limpio el buffer anterior para que quede libre y poderlo usar despues
		//de que lo cambie al final del frame
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		DrawObject(cube, cam, l);

		glfwSwapBuffers(window);
		//se ejecutan el resto de eventos, si es que hay
		glfwPollEvents();
	}
	glfwTerminate();

	return 0;
}
