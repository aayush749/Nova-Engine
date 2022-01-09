#include "CameraOrtho.h"

CameraOrtho::CameraOrtho(const glm::vec3& cameraPosition, float left, float right, float bottom, float top, float near, float far)
	:Camera(cameraPosition)
{
	auto viewMat = glm::translate(glm::mat4(1.0f), cameraPosition);
	auto projMat = glm::ortho(left, right, bottom, top, near, far);

	SetViewMat(viewMat);
	SetProjectionMat(projMat);
}
