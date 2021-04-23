#include "GLRender.h"
#include "TriangleRot.h"
#include<iostream>
#include "Time.h"
#include "World.h"
#include "Cube.h"
#include <pugixml.hpp>
#include "FileManager.h"
#include "InputManager.h"


GLint Init()
{
	//glfwInit();
	GLint initialization = glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);

	return initialization;
}

World* CreateWorld()
{
	World *world = new World();

	FileManager fman;
	char* vs = fman.GetFileContents("data/vertexShader.txt");
	char* fs = fman.GetFileContents("data/fragmentShader.txt");
	char* dfs = fman.GetFileContents("data/defaultFragmentShader.txt");
	GLSLShader *defaultShader = new GLSLShader(vs, dfs);
	GLSLShader *shader = new GLSLShader(vs, fs);
	State::defaultShader = defaultShader;
	
	Object3D* asianTown = new Object3D("data/asian_town.msh", shader);

	world->AddObject(asianTown);

	Camera *cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	world->AddCamera(cam);

	return world;
}
void SetupWorldObjects(World* world, GLRender* render) 
{
	for (int i = 0; i < world->GetObjectsSize(); ++i)
		render->SetupObject(world->GetObject(i));
}
void UpdateWorld(World* world, float deltaTime) 
{
	world->Update(deltaTime);
}

void RenderWorld(World*world, GLRender* render)
{
	State::lights.clear();
	for (int i = 0; i < world->GetLightsSize(); ++i) 
	{
		State::lights.push_back(world->GetLight(i));
	}
	
	world->GetActiveCamera()->Prepare();
	for (int i = 0; i < world->GetObjectsSize(); ++i)
		render->DrawObject(world->GetObject(i));
}

int main(int argc, char** argv)
{

	glfwInit();
	
	GLFWwindow*window = glfwCreateWindow(State::WindowSize.x, State::WindowSize.y, "APIS 3D", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	InputManager*input = new InputManager(window);
	glfwSetKeyCallback(window, KeyCallback);


	GLint GlewInitResult = Init();
	if (GlewInitResult != GLEW_OK)
	{
		printf("ERROR: %s",glewGetErrorString(GlewInitResult));
		exit(EXIT_FAILURE);
	}


	Time timeManager;
	World* world = CreateWorld();
	GLRender *render = new GLRender();

	SetupWorldObjects(world, render);

	while (!glfwWindowShouldClose(window))
	{
		timeManager.StartFrameTime();
		UpdateWorld(world, deltaTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		RenderWorld(world, render);

		glfwSwapBuffers(window);
		glfwPollEvents();

		timeManager.EndFrameTime();
	}
	glfwTerminate();
	return 0;
}