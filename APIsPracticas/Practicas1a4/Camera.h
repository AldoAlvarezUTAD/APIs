#pragma once
#include "Entity.h"

class Camera final :public Entity
{
public:
	Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up);
	~Camera();

	glm::mat4 view;
	glm::vec3 clearColor;

	void Prepare();
	void Update(float deltaTime);
private:
	glm::vec3 up;
	glm::vec3 lookAt;
};

