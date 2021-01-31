#pragma once
#include <glm/glm.hpp>
struct Vertex
{
	glm::vec4 position;
	glm::vec2 texCoord;

	void FlipUpsidedown();
};

