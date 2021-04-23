#pragma once
#include "Entity.h"
#include <glm/glm.hpp>

class Light :public Entity
{
public:
	enum class LightType { DIRECTIONAL, POINT, count };

	Light();
	~Light();

	void Prepare(int index, GLSLShader* shader) const;

	void SetColor(glm::vec3 col);
	void SetType(LightType t);
	void SetAttenuation(float att);

	glm::vec4 GetColor();
	LightType GetType();
	float GetAttenuation();

protected:
	float ClampValue(float val, float min, float max);
private:
	LightType type;
	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	float attenuation = 1;
};

