#pragma once
#include "Mesh3D.h"
#include "Material.h"
#include "Entity.h"
#include "FileManager.h"
#include "pugixml.hpp"


class Object3D : public Entity
{
public:
	Object3D();
	Object3D(const char* file, GLSLShader* shader);
	Object3D(std::vector<Mesh3D*>mesh, std::vector<Material*>material);

	std::vector<Material*>& materials;
	std::vector<Mesh3D*>& meshes;


	Mesh3D* GetMesh(size_t index);
	Material* GetMaterial(size_t index);

	size_t GetMeshCount();
	size_t GetMaterialsCount();

	void AddMesh(Mesh3D* mesh, Material* shader = nullptr);
	void SetMaterial(size_t index, Material*material);
	void ClearMeshes();

	void Update(float deltaTime);

protected:
	std::vector<Mesh3D*> _meshes;
	std::vector<Material*> _materials;

	bool isIndexOutOfRange(int index, int max);

	void LoadMesh(const char* file, GLSLShader* shader);
	Material* GetMaterialFromFileNode(pugi::xml_node matNode, GLSLShader*shader);
	Mesh3D* GetMeshFromFileNode(pugi::xml_node bufferNode);

	int ClampValue(int value, int min, int max);
};

