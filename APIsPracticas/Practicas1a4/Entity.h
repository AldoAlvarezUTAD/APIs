#pragma once
#include "GLSLShader.h"

class Entity
{
public:
	Entity();
	~Entity();

	glm::vec3 position;
	glm::vec3& rotation;
	glm::vec3& scale;

	void ResetTransform();

	void SetPosition(glm::vec3 pos);
	void Translate(glm::vec3 direction);
	void RotateAround(float degrees, glm::vec3 axis);
	void SetRotation(glm::vec3 rot);
	void Resize(glm::vec3 size);

	void CalculateModelMatrix();
	//Calculates and returns the Model Matrix for this entity
	glm::mat4x4 GetModelMatrix(); 

	virtual void Update(float deltaTIme) = 0;

protected:
	glm::mat4 Identity = glm::mat4(1.0f);
	glm::vec3 ones = glm::vec3(1.0f, 1.0f, 1.0f);

	glm::vec3 _rotation;
	glm::vec3 _scale;

private:
	glm::mat4 traslationMat;
	glm::mat4 rotationMat;
	glm::mat4 scaleMat;

	glm::mat4x4 Model;

};

