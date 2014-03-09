#pragma once

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace oglwork
{

class APP_EXPORTED_SYMBOL Camera
{
public:
	Camera();
	
	void SetProjection(float fovy, float aspect, float near, float far);
	void SetLookAt(const glm::vec3& from, const glm::vec3& to, const glm::vec3& up);

	void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const { return m_Position; }

	const glm::mat4& GetProjection() { return m_Projection; }
	const glm::mat4& GetView();

	void Pitch(float angle);
	void Roll(float angle);
	void Yaw(float angle);
	
	void Move(float distance);
	void Strafe(float distance);
	void Up(float distance);

private:
	void RecalculateView();

	glm::vec3 m_Position;
	glm::quat m_Orientation;

	glm::mat4 m_Projection;

	glm::mat4 m_View;
	bool m_ViewDirty;
};

}