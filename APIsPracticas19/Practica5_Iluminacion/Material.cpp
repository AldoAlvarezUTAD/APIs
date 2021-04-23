#include "Material.h"



Material::Material(Texture * _texture, GLSLShader * _shader)
{
	this->texture = _texture;
	this->shader = _shader;
}


Material::~Material()
{
}

void Material::Prepare()
{
	if (shader == nullptr)
		shader = State::defaultShader;

	shader->Use();
	shader->SetupAttributes();

	int model = glGetUniformLocation(shader->programID, "model");
	int totalLights = glGetUniformLocation(shader->programID, "totalLights");
	int diffuseColor = glGetUniformLocation(shader->programID, "diffuseColor");
	int shininessID = glGetUniformLocation(shader->programID, "matShininess");
	int lightAmb = glGetUniformLocation(shader->programID, "lightAmb");

	glUniformMatrix4fv(model, 1, GL_FALSE, &State::Model[0][0]);
	glUniform1i(totalLights, State::lights.size());
	glUniform4fv(diffuseColor, 1, &color[0]);
	glUniform1i(shininessID, shinniness);
	glUniform4fv(lightAmb, 1, &State::ambienLight[0]);


	for (int i = 0; i < State::lights.size(); ++i)
	{
		State::lights[i]->Prepare(i, shader);
	}


	if (texture != nullptr)
	{
		int texSampler = glGetUniformLocation(shader->programID, "texSampler");
		int textureCoords = glGetAttribLocation(shader->programID, "vtex");

		glEnableVertexAttribArray(textureCoords);
		glVertexAttribPointer(textureCoords, 2, GL_FLOAT, GL_FALSE,
			sizeof(Vertex), (void*)sizeof(glm::vec4));
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture->GetID());
		glUniform1i(texSampler, 0);
	}
}
