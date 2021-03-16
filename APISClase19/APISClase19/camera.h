#pragma once
#include <glm/glm.hpp>

struct camera
{
	glm::vec3 position;
	glm::vec3 lookAt;
	glm::vec3 up;
};

camera* CreateCamera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up);
void moveCamera(camera* cam);
glm::mat4 ComputeViewMatrix(camera* cam);
