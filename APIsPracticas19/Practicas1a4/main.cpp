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
	/*** practica 3 ***/
	//Texture * cubeSide = new Texture();
	//cubeSide->Load("data/front.png");
	//Texture * cubeTop = new Texture();
	//cubeTop->Load("data/top.png");

	FileManager fman;
	char* vs = fman.GetFileContents("data/vertexShader.txt");
	char* fs = fman.GetFileContents("data/fragmentShader.txt");
	char* dfs = fman.GetFileContents("data/defaultFragmentShader.txt");
	GLSLShader *defaultShader = new GLSLShader(vs, dfs);
	GLSLShader *shader = new GLSLShader(vs, fs);
	State::defaultShader = defaultShader;

	/*** practica 3 ***/
	//Material *materialSideCube = new Material(cubeSide, shader);
	//Material *materialTopCube = new Material(cubeTop, shader);

	//dibuja los triangulos de la practica 1
	//for (int x = -1; x <= 1; ++x) {
	//	for (int z = -2; z >= -4; --z) {
	//		TriangleRot *triangle = new TriangleRot(materialSideCube);
	//		triangle->position.x = x;
	//		triangle->position.z = z;
	//		world->AddObject(triangle);
	//	}
	//}

	/*** practica 3 ***/
	//Cube*cube = new Cube(materialTopCube, materialSideCube);
	/*** practica 3.5 ***/
	//Object3D*cube = new Object3D("data/cube.msh", shader);
	
	Object3D* asianTown = new Object3D("data/asian_town.msh", shader);
	//Object3D* asianTown = new Object3D("data/cube.msh", shader);

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