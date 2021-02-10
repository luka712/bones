#pragma once

#include "ControlsComponent.hpp"
#include "TransformComponent.hpp"
#include "glm/matrix.hpp"
#include "glm/ext.hpp"

using namespace glm;
using namespace Bones::Component;

namespace Bones
{
	namespace Shaders
	{
		namespace Material
		{
			class MaterialShader;
		}
	}
}

using Bones::Shaders::Material::MaterialShader;

namespace Bones
{
	namespace Camera
	{
		class BaseCamera
		{
		protected:
			BaseCamera();

			float m_fov = 60.0f, m_near = 0.1f, m_far = 100.0f, m_width = DEFAULT_WIDTH, m_height = DEFAULT_HEIGHT;
			vec3 m_worldUp = vec3(0, 1, 0);
			
			ControlsComponent* m_controls;

		public:
			TransformComponent* m_transform;
			mat4 m_viewMatrix, m_projectionMatrix;

			BaseCamera(mat4 viewMatrix, mat4 projectionMatrix);
			virtual ~BaseCamera() = 0;

			virtual const vec3 GetDirection() const noexcept = 0;

			void UseCamera(GLint projectionLocation, GLint viewLocation, GLint posLocation) const;
			void UseCamera(const MaterialShader& materialShader) const;

			virtual void Update() {};

			const mat4& GetViewMatrix() const { return m_viewMatrix; }
			const mat4& GetProjectionMatrix() const { return m_projectionMatrix; }
			TransformComponent& GetTransformComponent()const noexcept { return *m_transform; }
			ControlsComponent* GetControlComponent() { return m_controls; }
		};

	}
}
