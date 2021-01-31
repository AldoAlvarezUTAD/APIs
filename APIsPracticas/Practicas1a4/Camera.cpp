#include "Camera.h"
#include "State.h"
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up)
{
	SetPosition(pos);
	this->lookAt = lookAt;
	this->up = up;
	view = glm::lookAt(pos, lookAt, up); 	
}


Camera::~Camera()
{
}

void Camera::Prepare()
{
	State::View = view;
	State::Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
}

void Camera::Update(float deltaTime)
{
	lookAt = position;
	lookAt.z -= 1.0f;
	view = glm::lookAt(position, lookAt, up);
}
