#pragma once
#include "Object3D.h"

class TriangleRot: public Object3D
{
public:
	TriangleRot(Material *material);
	~TriangleRot();
	 void Update(float deltaTime);
};

