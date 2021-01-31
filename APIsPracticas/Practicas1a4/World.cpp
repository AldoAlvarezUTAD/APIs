#include "World.h"
#include <iterator>


World::World()
{
}


World::~World()
{
}

void World::AddObject(Object3D * obj) { objects.push_back(obj); }
void World::AddCamera(Camera * cam) { cameras.push_back(cam); }

void World::RemoveObject(Object3D * obj) { objects.remove(obj); }
void World::RemoveCamera(Camera * cam) { cameras.remove(cam); }

size_t World::GetObjectsSize() { return objects.size(); }
size_t World::GetCamerasSize() { return cameras.size(); }

Object3D* World::GetObject(size_t index) {
	if (isIndexOutOfRange(index, GetObjectsSize()))
		return nullptr;
	auto obj = objects.begin();
	std::advance(obj, index);
	return *obj;
}
Camera* World::GetCamera(size_t index) {
	if (isIndexOutOfRange(index, GetCamerasSize()))
		return nullptr;
	auto cam = cameras.begin();
	std::advance(cam, index);
	return *cam;
}

void World::Update(float deltaTime)
{
	for (auto obj = objects.begin(); obj != objects.end(); ++obj)
		(*obj)->Update(deltaTime);
	for (auto cam = cameras.begin(); cam != cameras.end(); ++cam)
		(*cam)->Update(deltaTime);
}
void World::SetActiveCamera(size_t index)
{
	if (isIndexOutOfRange(index, GetCamerasSize())) return;
	activeCamera = index;
}

int World::GetActiveCameraIndex()
{
	return activeCamera;
}

Camera * World::GetActiveCamera()
{
	return GetCamera(GetActiveCameraIndex());
}


bool World::isIndexOutOfRange(int index, int max)
{
	return index>=max;
}
