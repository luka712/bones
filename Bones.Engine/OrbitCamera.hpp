#pragma once


#include "BaseCamera.hpp"
#include "ControlsComponent.hpp"
#include "glm/ext.hpp"

using namespace glm;

namespace Bones
{
	namespace Camera
	{
		class OrbitCamera : public BaseCamera
		{
		private:
			float m_radius = 10.0f, m_moveForwardBackwardSpeed = 1.0f, m_yaw = -90, m_pitch = 0, m_speed = 0.6f;
			vec3 m_lookAt = vec3(0.0f, 0.0f, 0.0f);
			void UpdateMouse();


		public:
			OrbitCamera();
			~OrbitCamera();

			const vec3 GetDirection() const noexcept override { return normalize(m_lookAt); }

			void Update() override;
		};
	}
}
