#pragma once
#include<glm/glm.hpp>

#define DIR_LIGHT 0
#define SPOT_LIGHT 1

typedef struct light
{
	int type;
	glm::vec3 pos;
	glm::vec3 dir;
	glm::vec4 color;
}light;

light* createLight(int type, glm::vec3 pos, 
	glm::vec3 dir, 
	glm::vec4 color);