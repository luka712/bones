#include "FreeCamera.hpp"

using namespace Bones::Camera;

FreeCamera::FreeCamera() : BaseCamera()
{
	m_controls = new ControlsComponent();
}

void FreeCamera::UpdateMouse() 
{
	const MouseMove& mouseMove = m_controls->GetMouseMove();
	const MouseScroll& mouseScroll = m_controls->GetMouseScroll();

	m_yaw += mouseMove.X * m_turnSpeed;
	m_pitch -= mouseMove.Y * m_turnSpeed;

	if (m_pitch > 89.0f)
	{
		m_pitch = 89.0f;
	}

	if (m_pitch < -89.0f)
	{
		m_pitch = -89.0f;
	}

	if (mouseScroll.Y > 0)
	{
		m_fov -= m_zoomSpeed;
		m_projectionMatrix = perspective(radians(m_fov), m_width / m_height, m_near, m_far);
	}
	else if (mouseScroll.Y < 0)
	{
		m_fov += m_zoomSpeed;
		m_projectionMatrix = perspective(radians(m_fov), m_width / m_height, m_near, m_far);
	}
}

void FreeCamera::UpdateKeys() 
{
	auto pos = m_transform->GetPosition();

	if (m_controls->IsKeyPressed(SDLK_a))
	{
		pos -= m_right * m_speed;
	}
	else if (m_controls->IsKeyPressed(SDLK_d))
	{
		pos += m_right * m_speed;
	}
	
	if (m_controls->IsKeyPressed(SDLK_w))
	{
		pos += m_front * m_speed;
	}
	else if (m_controls->IsKeyPressed(SDLK_s))
	{
		pos -= m_front * m_speed;
	}

	m_transform->SetPosition(pos);
}

void FreeCamera::Update()
{
	UpdateMouse();

	m_front.x = cos(radians(m_yaw)) * cos(radians(m_pitch));
	m_front.y = sin(radians(m_pitch));
	m_front.z = sin(radians(m_yaw)) * cos(radians(m_pitch));
	m_front = normalize(m_front);

	m_right = normalize(cross(m_front, m_worldUp));
	m_up = normalize(cross(m_right, m_front));

	UpdateKeys();

	auto pos = m_transform->GetPosition();
	m_viewMatrix = lookAt(pos, pos + m_front, m_worldUp);
}

FreeCamera::~FreeCamera()
{
	delete m_controls;
	m_controls = nullptr;
}

