#pragma once
#include "Camera.h"
class CameraOrtho : public Camera
{
public:
	CameraOrtho(const glm::vec3& cameraPosition, float left, float right, float bottom, float top, float near, float far);
};

