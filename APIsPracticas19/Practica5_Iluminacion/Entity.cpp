#include "Entity.h"
#include <glm/gtx/transform.hpp>  
#include <glm/gtc/matrix_transform.hpp>
#include "State.h"

Entity::Entity():rotation(_rotation), scale(_scale)
{
}


Entity::~Entity()
{
}

void Entity::ResetTransform()
{
	position = glm::vec3(0.0f, 0.0f, 0.0f);
	rotation = glm::vec3(0.0f, 0.0f, 0.0f);
	scale = glm::vec3(1.0f, 1.0f, 1.0f);
}

void Entity::SetPosition(glm::vec3 pos) { position = pos; }

void Entity::Translate(glm::vec3 direction) { position += direction; }

void Entity::RotateAround(float degrees, glm::vec3 axis) { _rotation += degrees * axis; }

void Entity::SetRotation(glm::vec3 rot) { _rotation = rot; }

void Entity::Resize(glm::vec3 size) { _scale = size; }

void Entity::CalculateModelMatrix()
{
	Model = glm::translate(Identity, position);
	Model = glm::rotate(Model, rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	Model = glm::rotate(Model, rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	Model = glm::rotate(Model, rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	Model = glm::scale(Model, scale);
}

glm::mat4x4 Entity::GetModelMatrix()
{
	CalculateModelMatrix();
	return Model;
}