#include "Object.h"
#include "eventManager.h"
#include <string>
//#include "pugixml.hpp"
#include <pugixml.hpp>
#include <iostream>
//#include "shaderManager.h"
#include <sstream>

extern int defaultShaderID;



template <typename T>
T numberFromString(const std::string& str)
{
	T number;
	std::istringstream stream(str);
	stream >> number;
	return number;
}

template <typename T>
std::vector<T> splitString(const std::string& str, char delim)
{
	std::vector<T> elems;
	std::stringstream sstream(str);
	std::string item;

	if (str != "") {
		while (std::getline(sstream, item, delim)) {
			elems.push_back(numberFromString<T>(item));
		}
	}
	return elems;
}






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
	newObj->meshes = new std::vector<Mesh*>();
	newObj->meshes->push_back(new Mesh);

	newObj->meshes->at(0)->numVertex = 3;
	newObj->meshes->at(0)->vertexList = new std::vector<Vertex>();
	newObj->meshes->at(0)->vertexList->push_back(Vertex{ triangle[0], glm::vec2(1.0f, 1.0f)});
	newObj->meshes->at(0)->vertexList->push_back(Vertex{ triangle[1], glm::vec2(0.0f, 0.0f)});
	newObj->meshes->at(0)->vertexList->push_back(Vertex{ triangle[2], glm::vec2(1.0f, 0.0f)});

	newObj->meshes->at(0)->vertexIdx = new std::vector<unsigned int>();
	newObj->meshes->at(0)->vertexIdx->push_back(idxList[0]);
	newObj->meshes->at(0)->vertexIdx->push_back(idxList[1]);
	newObj->meshes->at(0)->vertexIdx->push_back(idxList[2]);

	newObj->pos[0] = newObj->pos[1] = newObj->pos[2] = 0.0f;
	newObj->rot[0] = newObj->rot[1] = newObj->rot[2] = 0.0f;
	newObj->scal[0] = newObj->scal[1] = newObj->scal[2] = 1.0f;
	
	newObj->pos.z = -1;

	//creo el material
	newObj->materials = new std::vector<Material*>();
	newObj->materials->push_back(new Material);
	newObj->materials->at(0)->texture = CreateTexture("data/front.png");

	return newObj;
}


void MoveObject(Object * obj)
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
void AddMesh(Object * obj, Mesh * mesh, Material * mat)
{
	obj->meshes->push_back(mesh);
	obj->materials->push_back(mat);
}

void LoadMesh(Object * obj, const char * meshFile)
{
	static int meshIDGenerator = 0;

	pugi::xml_document doc;
	//cargo el archivo
	pugi::xml_parse_result result = doc.load_file(meshFile);
	if (result) 
	{
		//accedo al primer elemento (meshes <list>)
		pugi::xml_node mesh = doc.child("mesh");
		pugi::xml_node buffers = mesh.child("buffers");

		for (pugi::xml_node bufferNode = buffers.child("buffer");
			bufferNode;
			bufferNode=bufferNode.next_sibling("buffer")) {
			pugi::xml_node materialNode = mesh.child("material");
		
			Material* mat = new Material;
			mat->shaderID = defaultShaderID;
			mat->texture = CreateTexture(materialNode.child("texture").text().as_string());

			Mesh * mesh = new Mesh;
			std::vector<float>vertList = splitString<float>(bufferNode.child("coords").text().as_string(),',');
			std::vector<int>idxVertList = splitString<int>(bufferNode.child("indices").text().as_string(), ',');;
			std::vector<float>textList = splitString<float>(bufferNode.child("texCoords").text().as_string(), ',');;
			mesh->meshID = meshIDGenerator;
			meshIDGenerator++;

			//de cuantos en cuantos se cuenta 1 vertice
			int vertexCompCount = bufferNode.child("coords").attribute("vertexCompCount").as_int();
			int texCoordCompCount = bufferNode.child("texCoords").attribute("texCoordCompCount").as_int();
		
			mesh->vertexList = new std::vector<Vertex>();
			//vertex iterator
			auto vit = vertList.begin();
			//texture coords iterator
			auto tcit = textList.begin();
			while(vit!=vertList.end())
			{
				float x = *vit; ++vit;
				float y = *vit; ++vit;
				float z = *vit; ++vit;
				float u = (*tcit); ++tcit;
				float v = (*tcit); ++tcit;

				mesh->vertexList->push_back(Vertex{ glm::vec4(x, y, z,1.0f), glm::vec2(u,v) });
				mesh->vertexIdx = new std::vector<unsigned int>();
				auto idxIt = idxVertList.begin();
				while (idxIt != idxVertList.end()) 
				{
					mesh->vertexIdx->push_back(*idxIt);
					idxIt++;
				}
			}
			AddMesh(obj, mesh, mat);
		}
	}
	else 
	{
		std::cout << result.description() << std::endl; return;
	}
}

//
//void SetShaderID(Object * obj, unsigned int shaderID)
//{
//	obj->material->shaderID = shaderID;
//}

void Vertex::FlipUpsdedown()
{
	texCoord.y = 1 - texCoord.y;
}

void Mesh::FlipUpsidedown()
{
	for (int i = 0; i < vertexList->size(); ++i)
		vertexList->at(i).FlipUpsdedown();
}

Object*CreateObjectFromFile(const char* fileName) 
{
	static unsigned int idGenerator = 0;
	Object*newObj = new Object[1];

	newObj->objID = idGenerator;
	idGenerator++;

	newObj->meshes = new std::vector<Mesh*>();
	newObj->materials = new std::vector<Material*>();

	LoadMesh(newObj, fileName);

	newObj->pos[0] = newObj->pos[1] = newObj->pos[2] = 0.0f;
	newObj->rot[0] = newObj->rot[1] = newObj->rot[2] = 0.0f;
	newObj->scal[0] = newObj->scal[1] = newObj->scal[2] = 1.0f;

	newObj->pos.z = -1;

	return newObj;
}