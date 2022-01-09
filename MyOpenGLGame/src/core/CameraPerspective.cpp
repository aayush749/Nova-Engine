#include "CameraPerspective.h"

//c-tor
CameraPerspective::CameraPerspective(const glm::vec3& cameraPosition, float near, float far, float width, float height)
    :Camera(cameraPosition)
{
    auto viewMat = glm::translate(glm::mat4(1.0f), cameraPosition);
    auto projMat = glm::perspective((float)glm::radians(60.), width / height , near, far);

    SetViewMat(viewMat);
    SetProjectionMat(projMat);
}
