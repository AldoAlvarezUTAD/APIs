#pragma once
#include "GLSLShader.h"
#include "Texture.h"
#include "State.h"

class Material
{
public:
	Material(Texture * _texture = nullptr, GLSLShader * _shader = nullptr);
	~Material();

	GLSLShader* shader;
	Texture * texture;

	void Prepare();

	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	unsigned int shinniness = 0;
private:

};

