#include "GLRender.h"
#include "TriangleRot.h"
#include<iostream>
#include "Time.h"
#include "World.h"
#include "Cube.h"

const char* defaultVertexShader = "\n\
#version 330\n\
\n\
uniform mat4 MVP;\n\
in vec4 vpos;\n\
out vec4 vertexColor;\n\
\n\
void main()\n\
{\n\
\n\
gl_Position=MVP*vpos;\n\
vertexColor=vec4(1.0f,1.0f,1.0f,1.0f);\n\
\n\
}\n\
";


const char* defaultFragmentShader = "\n\
#version 330\n\
\n\
in vec4 vertexColor;\n\
out vec4 fragColor;\n\
\n\
void main()\n\
{\n\
\n\
fragColor=vertexColor;\n\
\n\
}\n\
";




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
	Texture * cubeSide = new Texture();
	cubeSide->Load("data/front.png");
	Texture * cubeTop = new Texture();
	cubeTop->Load("data/top.png");

	GLSLShader *defaultShader = new GLSLShader(defaultVertexShader, defaultFragmentShader);
	GLSLShader *shader = new GLSLShader(vertexShader, fragmentShader);
	State::defaultShader = defaultShader;

	Material *materialSideCube = new Material(cubeSide, shader);
	Material *materialTopCube = new Material(cubeTop, shader);

	//for (int x = -1; x <= 1; ++x) {
	//	for (int z = -2; z >= -4; --z) {
	//		TriangleRot *triangle = new TriangleRot(materialSideCube);
	//		triangle->position.x = x;
	//		triangle->position.z = z;
	//		world->AddObject(triangle);
	//	}
	//}

	Cube*cube = new Cube(materialTopCube, materialSideCube);
	world->AddObject(cube);

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
	
	GLFWwindow*window = glfwCreateWindow(600, 400, "APIS 3D", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	//glfwSetKeyCallback(window, keyCallback);

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