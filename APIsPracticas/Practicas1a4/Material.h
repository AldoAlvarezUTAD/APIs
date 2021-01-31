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
private:

};

