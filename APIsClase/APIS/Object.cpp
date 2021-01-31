#include "Object.h"
#include "eventManager.h"
#include <string>

Object * CreateTriangle()
{
	static unsigned int idGenerator = 0;
	glm::vec4 triangle[3] = { glm::vec4(0.5f, 1.0f, 0.0f, 1.0f),
							  glm::vec4(-0.5f, 0.0f, 0.0f, 1.0f),
							  glm::vec4(0.5f, 0.0f, 0.0f, 1.0f) };

	int idxList[3] = { 0,2,1 };

	Object*newObj = new Object[1];

	newObj->objID = idGenerator;
	idGenerator++;
	newObj->mesh = new Mesh;

	newObj->mesh->numVertex = 3;
	newObj->mesh->vertexList = new std::vector<Vertex>();
	newObj->mesh->vertexList->push_back(Vertex{ triangle[0], glm::vec2(1.0f, 1.0f)});
	newObj->mesh->vertexList->push_back(Vertex{ triangle[1], glm::vec2(0.0f, 0.0f)});
	newObj->mesh->vertexList->push_back(Vertex{ triangle[2], glm::vec2(1.0f, 0.0f)});

	newObj->mesh->vertexIdx = new std::vector<unsigned int>();
	newObj->mesh->vertexIdx->push_back(idxList[0]);
	newObj->mesh->vertexIdx->push_back(idxList[1]);
	newObj->mesh->vertexIdx->push_back(idxList[2]);

	newObj->pos[0] = newObj->pos[1] = newObj->pos[2] = 0.0f;
	newObj->rot[0] = newObj->rot[1] = newObj->rot[2] = 0.0f;
	newObj->scal[0] = newObj->scal[1] = newObj->scal[2] = 1.0f;
	
	newObj->pos.z = -1;

	//creo el material
	newObj->material = new Material;
	newObj->material->texture = CreateTexture("data/front.png");

	return newObj;
}


void MoveTriangle(Object * obj)
{
	if (keybEvent[GLFW_KEY_A])
	{
		obj->pos.x -= 0.001f;
	}
	if (keybEvent[GLFW_KEY_D])
	{
		obj->pos.x += 0.001f;
	}

	if (keybEvent[GLFW_KEY_J])
	{
		obj->rot.y -= 0.001f;
	}
	if (keybEvent[GLFW_KEY_L])
	{
		obj->rot.y += 0.001f;
	}
	if (keybEvent[GLFW_KEY_Z])
	{
		obj->scal.x -= 0.001f;
		obj->scal.y -= 0.001f;
		obj->scal.z -= 0.001f;
	}
	if (keybEvent[GLFW_KEY_X])
	{
		obj->scal.x += 0.001f;
		obj->scal.y += 0.001f;
		obj->scal.z += 0.001f;
	}
}

void SetShaderID(Object * obj, unsigned int shaderID)
{
	obj->material->shaderID = shaderID;
}

void Vertex::FlipUpsdedown()
{
	texCoord.y = 1 - texCoord.y;
}

void Mesh::FlipUpsidedown()
{
	for (int i = 0; i < vertexList->size(); ++i)
		vertexList->at(i).FlipUpsdedown();
}
