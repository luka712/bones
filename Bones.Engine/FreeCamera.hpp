#pragma once

#include "BaseCamera.hpp"
#include "ControlsComponent.hpp"
#include "glm/ext.hpp"

using namespace glm;

namespace Bones
{
	namespace Camera
	{
		class FreeCamera : public BaseCamera
		{
		private:
			float m_yaw = -90, m_pitch = 0, m_speed = 0.35f, m_turnSpeed = 0.5f, m_zoomSpeed = 2.0f;
			vec3 m_front = vec3(0, 0, 0), m_right = vec3(0, 0, 0), m_up = vec3(0, 0, 0);

			void UpdateMouse();
			void UpdateKeys();

		public:
			FreeCamera();
			~FreeCamera();

			const vec3 GetDirection() const noexcept override { return normalize(m_front); }

			void Update() override;
		};
	}
}
