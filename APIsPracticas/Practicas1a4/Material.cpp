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
