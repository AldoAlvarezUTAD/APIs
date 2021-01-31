#include "State.h"

glm::mat4 State::Model = glm::mat4(1.0f);
glm::mat4 State::View = glm::mat4(1.0f);
glm::mat4 State::Projection = glm::mat4(1.0f);
GLSLShader *State::defaultShader = nullptr;


glm::mat4 State::GetMVP()
{
	return Projection * View * Model;
}
