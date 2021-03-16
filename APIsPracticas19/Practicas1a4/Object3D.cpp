#include "Object3D.h"
#include <glm/gtx/transform.hpp>  
#include <glm/gtc/matrix_transform.hpp>


Object3D::Object3D(): materials(_materials), meshes(_meshes)
{
	ResetTransform();
}

Object3D::Object3D(const char* file, GLSLShader* shader) : materials(_materials), meshes(_meshes)
{
	LoadMesh(file, shader);
	ResetTransform();
}

Object3D::Object3D(std::vector<Mesh3D*>mesh, std::vector<Material*>material): materials(_materials), meshes(_meshes)
{
	ResetTransform();

	for (int i = 0; i < mesh.size(); ++i)
		_meshes.push_back(mesh[i]);
	for (int i = 0; i < _materials.size(); ++i)
		_materials.push_back(material[i]);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// DRAW METHODS ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mesh3D * Object3D::GetMesh(size_t index)
{
	if (isIndexOutOfRange(index, GetMeshCount()))
		return nullptr;
	return _meshes[index];
}

Material * Object3D::GetMaterial(size_t index)
{
	if (isIndexOutOfRange(index, GetMaterialsCount()))
		return nullptr;
	return _materials[index];
}

size_t Object3D::GetMeshCount() { return _meshes.size(); }
size_t Object3D::GetMaterialsCount() { return _materials.size(); }

void Object3D::AddMesh(Mesh3D * mesh, Material * material)
{
	_meshes.push_back(mesh);
	_materials.push_back(material);
}

void Object3D::SetMaterial(size_t index, Material*material)
{
	if (isIndexOutOfRange(index, GetMaterialsCount()))
		return;
	_materials.at(index) = material;
}

void Object3D::ClearMeshes()
{
	_meshes.clear();
	_materials.clear();
}

void Object3D::Update(float deltaTime)
{
	//rotation.y += 1.0f * deltaTime;
	//rotation.x += 0.6f * deltaTime;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HELPER METHODS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Object3D::isIndexOutOfRange(int index, int max)
{
	return index >= max;
}

void Object3D::LoadMesh(const char* file, GLSLShader* shader)
{
	pugi::xml_document doc;
	//cargo el archivo
	pugi::xml_parse_result result = doc.load_file(file);
	if (result)
	{
		//accedo al primer elemento (meshes <list>)
		pugi::xml_node mesh = doc.child("mesh");
		pugi::xml_node buffers = mesh.child("buffers");

		for (pugi::xml_node bufferNode = buffers.child("buffer");
			bufferNode;
			bufferNode = bufferNode.next_sibling("buffer"))
		{
			Material* mat = GetMaterialFromFileNode(bufferNode.child("material"), shader);
			Mesh3D* mesh = GetMeshFromFileNode(bufferNode); 
		
			AddMesh(mesh, mat);
		}
	}
	else
	{
		std::cout << result.description() << std::endl; return;
	}
}

Material * Object3D::GetMaterialFromFileNode(pugi::xml_node matNode, GLSLShader* shader)
{
	Material* mat = new Material;
	mat->shader = shader;
	mat->texture = new Texture();
	mat->texture->Load(matNode.child("texture").text().as_string());
	return mat;
}

Mesh3D* Object3D::GetMeshFromFileNode(pugi::xml_node bufferNode)
{
	Mesh3D* mesh = new Mesh3D;
	std::vector<float>vertList = splitString<float>(bufferNode.child("coords").text().as_string(), ',');
	std::vector<int>idxVertList = splitString<int>(bufferNode.child("indices").text().as_string(), ',');;
	std::vector<float>textList = splitString<float>(bufferNode.child("texCoords").text().as_string(), ',');;

	//de cuantos en cuantos se cuenta 1 vertice
	int vertexCompCount = ClampValue(bufferNode.child("coords").attribute("vertexCompCount").as_int(), 0, 3);
	int texCoordCompCount = ClampValue(bufferNode.child("texCoords").attribute("texCoordCompCount").as_int(), 0, 2);

	//vertex iterator
	auto vit = vertList.begin();
	//texture coords iterator
	auto tcit = textList.begin();
	float pos[3]{ 0.0f,0.0f,0.0f };
	float uv[2]{ 0.0f,0.0f };
	while (vit != vertList.end())
	{
		for (int i = 0; i < vertexCompCount; ++i) 
		{
			pos[i] = (*vit); ++vit;
		}
		for (int i = 0; i < texCoordCompCount; ++i) {
			uv[i] = (*tcit); ++tcit;
		}

		mesh->AddVertex(Vertex{ glm::vec4(pos[0], pos[1], pos[2], 1.0f), glm::vec2(uv[0], uv[1]) });
	}

	int idx[3]{ 0,0,0 };
	auto idxIt = idxVertList.begin();
	while (idxIt != idxVertList.end())
	{
		idx[0] = (*idxIt); idxIt++;
		idx[1] = (*idxIt); idxIt++;
		idx[2] = (*idxIt); idxIt++;
		mesh->AddTriangleIdx(idx[0], idx[1], idx[2]);
	}
	return mesh;
}

int Object3D::ClampValue(int value, int min, int max)
{
	if (value > max)return max;
	if (value < min)return min;
	return value;
}
