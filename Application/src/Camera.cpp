#include "stdafx.h"

#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

namespace oglwork
{

Camera::Camera()
: m_Position(0.f)
, m_Orientation(0, 0, 0, 1)
, m_Projection(glm::mat4(1.0f))
, m_View(glm::mat4(1.0f))
, m_ViewDirty(false)
{}

void Camera::SetProjection(float fovy, float aspect, float near, float far)
{
	m_Projection = glm::perspective(fovy, aspect, near, far);
}

void Camera::SetLookAt(const glm::vec3& from,
	const glm::vec3& to,
	const glm::vec3& up)
{
	auto mat = glm::lookAt(from, to, up);

	m_Position = from;

	m_Orientation = glm::quat_cast(mat);

	m_ViewDirty = true;
}

void Camera::SetPosition(const glm::vec3& position)
{
	m_Position = position;
	m_ViewDirty = true;
}

const glm::mat4& Camera::GetView()
{
	if (m_ViewDirty)
	{
		RecalculateView();
	}

	return m_View;
}

void Camera::RecalculateView()
{
	auto translation = glm::translate(glm::mat4(1.0f), m_Position);
	auto rotation = glm::mat4_cast(m_Orientation);

	m_View = translation * rotation;
	m_ViewDirty = false;
}

void Camera::Pitch(float angle)
{
	auto rotationAxis = m_Orientation * glm::vec3(1, 0, 0) * m_Orientation;
	m_Orientation = glm::rotate(m_Orientation, angle, rotationAxis);
	m_Orientation = glm::normalize(m_Orientation);
	m_ViewDirty = true;
}

void Camera::Roll(float angle)
{
	auto rotationAxis = m_Orientation * glm::vec3(0, 0, -1) * m_Orientation;
	m_Orientation = glm::rotate(m_Orientation, angle, rotationAxis);
	m_Orientation = glm::normalize(m_Orientation);
	m_ViewDirty = true;
}

void Camera::Yaw(float angle)
{
	// FPS-style camera
	m_Orientation = glm::rotate(m_Orientation, angle, glm::vec3(0, 1, 0));
	m_Orientation = glm::normalize(m_Orientation);
	m_ViewDirty = true;
}

void Camera::Move(float distance)
{
	m_Position += (m_Orientation * glm::vec3(0, 0, -1) * m_Orientation) * distance;
	m_ViewDirty = true;
}

void Camera::Strafe(float distance)
{
	m_Position += (m_Orientation * glm::vec3(1, 0, 0) * m_Orientation) * distance;
	m_ViewDirty = true;
}

void Camera::Up(float distance)
{
	m_Position += (m_Orientation * glm::vec3(0, 1, 0) * m_Orientation) * distance;
	m_ViewDirty = true;
}

}