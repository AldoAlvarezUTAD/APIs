#pragma once
#include <glm/glm.hpp>
#include "GLSLShader.h"

//General Variables
class State
{
public:
	static GLSLShader* defaultShader;

	static glm::mat4 Projection;
	static glm::mat4 View;
	static glm::mat4 Model;

	static glm::mat4 GetMVP();

	static glm::vec2 WindowSize;

};
