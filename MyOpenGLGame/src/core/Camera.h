#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GL/glew.h>


// TODO: Should break this class into orthographic and perspective camera types. Currently only perspective mode is supported.
class Camera
{
public:
	const glm::mat4& getProjectionMat() const;
	const glm::vec3& getPosition() const;
	const glm::mat4& getViewMat() const;
	void translateByAmt(glm::vec3&& amtTransVec);
	void rotateByAmtandAxis(const float& degrees, const glm::vec3& rotAxis);
	void moveX(const float amt);
	void moveY(const float amt);
	void moveZ(const float amt);
	void rotX(const float degrees);
	void rotY(const float degrees);
	void rotZ(const float degrees);

public:
	Camera(const glm::vec3& cameraPosition, float near, float far, float width, float height);

private:
	glm::mat4 m_ProjMat, m_ViewMat;
	glm::vec3 m_Pos;

private:
	// Call this every time the camera position is updated
	void updateViewMat();
};