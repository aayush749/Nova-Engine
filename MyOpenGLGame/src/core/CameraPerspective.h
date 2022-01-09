#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include "Camera.h"

class CameraPerspective : public Camera
{
public:
	CameraPerspective(const glm::vec3& cameraPosition, float near, float far, float width, float height);
};