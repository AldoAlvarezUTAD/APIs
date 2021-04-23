#include "Light.h"
#include <string>

Light::Light()
{
	ResetTransform();
	color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
}

Light::~Light()
{
}

void Light::Prepare(int index, GLSLShader* shader) const
{
	int id = shader->programID;
	std::string s_idx = std::to_string(index);
	std::string lt = "lightType[" + s_idx + "]";
	std::string lp = "lightPos[" + s_idx + "]";
	std::string ld = "lightDir[" + s_idx + "]";

	glUniform1i(glGetUniformLocation(id, lt.c_str()), (int)type);
	glUniform3fv(glGetUniformLocation(id, lp.c_str()), 1, &position[0]);
	glUniform3fv(glGetUniformLocation(id, ld.c_str()), 1, &rotation[0]);
	//glUniform3fv(glGetUniformLocation(id, "eyePos[" + gl_idx + "]"), 1, &cam->position[0]);
	//glUniform3fv(glGetUniformLocation(id, "lookAt[" + gl_idx + "]"), 3, &cam->lookAt[0]);
}

void Light::SetColor(glm::vec3 col)
{
	for (int i = 0; i < 3; ++i)
		color[i] = ClampValue(col[i], 0.0f, 1.0f);
}

void Light::SetType(Light::LightType t)
{
	if ((int)t < 0)t = (LightType)0;
	else if (t >= LightType::count)t = (LightType)((int)(LightType::count)-1);
	type = t;
}

glm::vec4 Light::GetColor()
{
	return color;
}

Light::LightType Light::GetType()
{
	return type;
}

float Light::ClampValue(float val, float min, float max)
{
	if (val < min)return min;
	if (val > max)return max;
	return val;
}
