#pragma once
#include "Object3D.h"
class Cube:public Object3D
{
public:
	Cube(Material*top, Material*side);
	~Cube();

	void Update(float deltaTime);
};

