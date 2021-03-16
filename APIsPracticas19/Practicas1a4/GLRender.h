#pragma once
#include "World.h"
#include<map>

class GLRender
{
public:
	struct glMeshAttributes {
		unsigned int bufferID;
		unsigned int vertexArrayID;
		unsigned int indexArrayID;
	};

	GLRender();
	~GLRender();

	void SetupObject(Object3D*obj);
	void DrawObject(Object3D* obj);
	void DrawWorld(World* world);

private:
	std::map<unsigned int, glMeshAttributes>MeshIDs;
};

