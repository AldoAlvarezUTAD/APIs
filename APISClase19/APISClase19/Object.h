#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"


struct Material
{
	Texture* texture;
	int shaderID;
};

struct Vertex {
	glm::vec4 position;
	glm::vec2 texCoord;

	void FlipUpsdedown();
};

struct Mesh
{
	int meshID;
	std::vector<Vertex>* vertexList;
	std::vector<unsigned int>* vertexIdx; //índice / orden de los vertices para la triangulacion
	int numVertex;

	void FlipUpsidedown();
};

struct Object
{
	int objID;
	glm::vec3 pos;
	glm::vec3 rot;
	glm::vec3 scal;
	std::vector<Mesh*>* meshes;
	std::vector<Material*>* materials;
};

Object* CreateTriangle();
void MoveObject(Object* obj);
//void SetShaderID(Object*obj, unsigned int shaderID);
void AddMesh(Object* obj, Mesh* mesh, Material* mat);
void LoadMesh(Object* obj, const char* meshFile);
Object* CreateObjectFromFile(const char* fileName);

//std::vector<std::string> splitString(const std::string& str, char delim);