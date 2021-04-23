#pragma once
#include "Object3D.h"
#include "Camera.h"
#include <list>

//app manager
class World
{
public:
	World();
	~World();

	void AddObject(Object3D * obj);
	void AddCamera(Camera * cam);
	void AddLight(Light* light);

	void RemoveObject(Object3D * obj);
	void RemoveCamera(Camera * cam);
	void RemoveLight(Light * light);

	size_t GetObjectsSize();
	size_t GetCamerasSize();
	size_t GetLightsSize();

	Object3D* GetObject(size_t index);
	Camera* GetCamera(size_t index);
	Light* GetLight(size_t index);

	void Update(float deltaTime);

	void SetActiveCamera(size_t index);
	int GetActiveCameraIndex();
	Camera* GetActiveCamera();

	glm::vec3 Ambient;

private:
	std::list<Object3D*>objects;
	std::list<Camera*>cameras;
	std::list<Light*>lights;
	int activeCamera = 0;

	bool isIndexOutOfRange(int index, int max);

};
