#include "camera.h"
#include "eventManager.h"
#include <glm/gtc/matrix_transform.hpp>

camera* CreateCamera(glm::vec3 pos, glm::vec3 lookAt, glm::vec3 up)
{
	camera* cam = new camera;
	cam->position = pos;
	cam->lookAt = lookAt;
	cam->up = up;
	return cam;
}

void moveCamera(camera* cam)
{
	if (keybEvent[GLFW_KEY_UP])
	{
		cam->position.y += 0.001f;
	}
	if (keybEvent[GLFW_KEY_DOWN])
	{
		cam->position.y -= 0.001f;
	}
	if (keybEvent[GLFW_KEY_LEFT])
	{
		cam->position.x -= 0.001f;
	}
	if (keybEvent[GLFW_KEY_RIGHT])
	{
		cam->position.x += 0.001f;
	}
	if (keybEvent[GLFW_KEY_W])
	{
		cam->position.z -= 0.001f;
	}
	if (keybEvent[GLFW_KEY_S])
	{
		cam->position.z += 0.001f;
	}
	cam->lookAt = cam->position;
	cam->lookAt.z -= 1.0f;
}

glm::mat4 ComputeViewMatrix(camera* cam)
{
	return glm::lookAt(cam->position, cam->lookAt, cam->up);
}