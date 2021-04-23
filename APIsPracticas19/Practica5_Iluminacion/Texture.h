#pragma once
#include <glm/glm.hpp>
class Texture
{
public:
	Texture();
	~Texture();

	void Load(const char* filePath);
	unsigned int GetID();
	const glm::ivec2& getSize() const;
	void bind() const;

private:
	unsigned int ID;
	glm::ivec2 size;
};

