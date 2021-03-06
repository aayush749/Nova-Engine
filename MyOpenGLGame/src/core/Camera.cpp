#include "Camera.h"


const glm::mat4& Camera::getProjectionMat() const
{
    return m_ProjMat;
}

const glm::vec3& Camera::getPosition() const
{
    return m_Pos;
}

const glm::mat4& Camera::getViewMat() const
{
    return m_ViewMat;
}

void Camera::translateByAmt(glm::vec3&& amtTransVec)
{
    if (amtTransVec != glm::vec3())
    {
        amtTransVec.x *= -1;  //To simulate proper camera motion
        m_Pos += amtTransVec;
        //m_ViewMat = glm::translate(glm::mat4(1.0f), m_Pos);
        updateViewMat(amtTransVec);
    }
}

void Camera::rotateByAmtandAxis(const float& degrees, const glm::vec3& rotAxis)
{
    m_ViewMat = glm::rotate(m_ViewMat, glm::radians(degrees), rotAxis);
}

void Camera::moveX(const float amt)
{
    m_Pos.x -= amt;
    updateViewMat();
}

void Camera::moveY(const float amt)
{
    m_Pos.y += amt;
    updateViewMat();
}

void Camera::moveZ(const float amt)
{
    m_Pos.z += amt;
    updateViewMat();
}

void Camera::rotX(const float degrees)
{
    m_ViewMat = glm::rotate(glm::radians(degrees), glm::vec3(1., 0., 0.));
}

void Camera::rotY(const float degrees)
{
    m_ViewMat = glm::rotate(glm::radians(degrees), glm::vec3(0., 1., 0.));
}

void Camera::rotZ(const float degrees)
{
    m_ViewMat = glm::rotate(glm::radians(degrees), glm::vec3(0., 0., 1.));
}


//c-tor
Camera::Camera(const glm::vec3& cameraPosition)
    :m_Pos(cameraPosition)
{}

void Camera::updateViewMat()
{
    // reposition the camera to the camera position
    m_ViewMat = glm::translate(glm::mat4(1.0f), m_Pos);
}

void Camera::updateViewMat(const glm::vec3& amountVec)
{
    m_ViewMat = glm::translate(m_ViewMat, amountVec);
}

void Camera::SetViewMat(const glm::mat4& viewMat)
{
    m_ViewMat = viewMat;
}

void Camera::SetProjectionMat(const glm::mat4& projMat)
{
    m_ProjMat = projMat;
}
