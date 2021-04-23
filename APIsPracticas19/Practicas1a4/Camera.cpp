#include "Camera.h"
#include "State.h"
#include <glm/gtc/matrix_transform.hpp>
#include "InputManager.h"

Camera::Camera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up)
{
	SetPosition(pos);
	clearColor = glm::vec3(0.0f, 0.0f, 0.0f);
	this->lookAt = lookAt;
	this->up = up;
	forward = glm::normalize(lookAt - pos);
	right = glm::cross(up, forward);

	view = glm::lookAt(pos, lookAt, up); 	
	rotation.x = rotation.y = rotation.z = 0;
}


Camera::~Camera()
{
}

void Camera::Prepare()
{
	State::View = view;
	State::Projection = glm::perspective(glm::radians(45.0f), 4.0f / 3.0f, 0.01f, 100.0f);
	glClearColor(clearColor.r, clearColor.g, clearColor.b, 1.0f);
}

void Camera::Update(float deltaTime)
{
	forward = glm::normalize(lookAt - position);
	right = glm::cross(up, forward);
	Move(deltaTime);
	Rotate(deltaTime);

	lookAt = position;
	lookAt.z -= 1.0f;
	RotateLookAt();
	view = glm::lookAt(position, lookAt, up);
}

void Camera::Move(float deltaTime)
{
	float modifier = 0.0f;
	if (isKeyDown(GLFW_KEY_LEFT_SHIFT) || isKeyDown(GLFW_KEY_RIGHT_SHIFT))
		modifier = 1.0f - movementSpeed;
	if (isKeyDown(GLFW_KEY_UP) || isKeyDown(GLFW_KEY_W))
		position += forward * (movementSpeed+modifier) * deltaTime;
	if (isKeyDown(GLFW_KEY_DOWN) || isKeyDown(GLFW_KEY_S))
		position -= forward * (movementSpeed + modifier) * deltaTime;

	if (isKeyDown(GLFW_KEY_I))
		position += up * (movementSpeed + modifier) * deltaTime;
	if (isKeyDown(GLFW_KEY_K))
		position -= up * (movementSpeed + modifier) * deltaTime;
}

void Camera::Rotate(float deltaTime)
{
	if (isKeyDown(GLFW_KEY_RIGHT) || isKeyDown(GLFW_KEY_D))
		rotation.y -= rotationSpeed*deltaTime;
	if (isKeyDown(GLFW_KEY_LEFT) || isKeyDown(GLFW_KEY_A))
		rotation.y += rotationSpeed * deltaTime;
}

void Camera::RotateLookAt()
{

	glm::mat4 Model = glm::translate(Identity, lookAt);
	Model = glm::rotate(Model, rotation.y, up);

	lookAt.x = Model[0][0];
	lookAt.y = Model[0][1];
	lookAt.z = Model[0][2];
}
