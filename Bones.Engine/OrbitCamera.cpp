#include "OrbitCamera.hpp"

using namespace Bones::Camera;

OrbitCamera::OrbitCamera()
{
	m_controls = new ControlsComponent();
}

void OrbitCamera::UpdateMouse()
{
	const MouseMove& mouseMove = m_controls->m_mouseMove;
	const MouseScroll& mouseScroll = m_controls->m_mouseScroll;
	const MouseBtnPressed& mouseBtnPressed = m_controls->m_mouseBtnPressed;

	if (mouseBtnPressed.Left)
	{
		m_yaw += mouseMove.X * m_speed;
		m_pitch += mouseMove.Y * m_speed;

		if (m_pitch > 89.0f)
		{
			m_pitch = 89.0f;
		}

		if (m_pitch < -89.0f)
		{
			m_pitch = -89.0f;
		}
	}

	if (mouseScroll.Y > 0)
	{
		m_radius -= m_moveForwardBackwardSpeed;
	}
	else if (mouseScroll.Y < 0)
	{
		m_radius += m_moveForwardBackwardSpeed;
	}

	float x = m_radius * cos(radians(m_yaw)) * cos(radians(m_pitch));
	float y = m_radius * sin(radians(m_pitch));
	float z = m_radius * sin(radians(m_yaw)) * cos(radians(m_pitch));

	m_transform->SetPosition(x, y, z);
}

void OrbitCamera::Update()
{
	UpdateMouse();

	this->m_transform->GetPosition();


	m_viewMatrix = lookAt(m_transform->GetPosition(), m_lookAt, m_worldUp);
}

OrbitCamera::~OrbitCamera()
{
	delete m_controls;
	m_controls = nullptr;
}
