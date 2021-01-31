#include "Object3D.h"
#include <glm/gtx/transform.hpp>  
#include <glm/gtc/matrix_transform.hpp>

Object3D::Object3D(): materials(_materials), meshes(_meshes)
{
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// HELPER METHODS /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Object3D::isIndexOutOfRange(int index, int max)
{
	return index >= max;
}
