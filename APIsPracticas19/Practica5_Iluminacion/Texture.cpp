#include "Texture.h"
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


Texture::Texture()
{
	size = glm::vec2(0, 0);
}


Texture::~Texture()
{
}

void Texture::Load(const char * filePath)
{
	unsigned char * data = stbi_load(filePath, &size.x, &size.y, NULL, STBI_rgb_alpha);
	glGenTextures(1, &ID);

	bind();
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x,size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(data);
}

unsigned int Texture::GetID() { return ID; }

const glm::ivec2 & Texture::getSize() const { return size; }

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, ID);
}
