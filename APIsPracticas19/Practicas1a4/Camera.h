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
	glm::vec3 forward;
	glm::vec3 right;

	glm::vec3 lookAt;
	float movementSpeed = 1.0f;
	float rotationSpeed = 1.0f;

	void Move(float deltaTime);
	void Rotate(float deltaTime);
	void RotateLookAt();
};

