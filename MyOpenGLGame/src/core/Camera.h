#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camera
{
public:
	virtual const glm::mat4& getProjectionMat() const;
	virtual const glm::vec3& getPosition() const;
	virtual const glm::mat4& getViewMat() const;
	virtual void translateByAmt(glm::vec3&& amtTransVec);
	virtual void rotateByAmtandAxis(const float& degrees, const glm::vec3& rotAxis);
	virtual void moveX(const float amt);
	virtual void moveY(const float amt);
	virtual void moveZ(const float amt);
	virtual void rotX(const float degrees);
	virtual void rotY(const float degrees);
	virtual void rotZ(const float degrees);

protected:
	//ctor
	Camera(const glm::vec3& cameraPosition);
	
	virtual void SetViewMat(const glm::mat4& viewMat);
	virtual void SetProjectionMat(const glm::mat4& projMat);
private:
	// Call this every time the camera position is updated
	virtual void updateViewMat();
	virtual void updateViewMat(const glm::vec3&);

private:
	glm::mat4 m_ProjMat, m_ViewMat;
	glm::vec3 m_Pos;
};

