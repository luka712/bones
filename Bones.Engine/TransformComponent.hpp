#pragma once

#include "glm/matrix.hpp"
#include "glm/vec3.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext.hpp"
#include "BaseComponent.hpp"

using glm::vec3;
using glm::vec4;
using glm::mat4;
using glm::length;

namespace Bones
{
	namespace Component
	{
		class TransformComponent final : public Bones::Component::BaseComponent
		{
		public:
			vec3 m_position;
			vec3 m_rotation;
			vec3 m_scale;
			mat4 m_transform;
			TransformComponent();

			const mat4& GetMatrix() const { return m_transform; }

			const vec3& GetPosition() const { return m_position; }
			TransformComponent& SetPosition(const vec3& pos);
			TransformComponent& SetPosition(float x, float y, float z);

			const vec3& GetScale() const { return m_scale; }
			TransformComponent& SetScale(const vec3& scale);
			TransformComponent& SetScale(float x, float y, float z);

			void Initialize() override {}
			void Update() override;

			void UseTransform(GLint transformLocation) const;

			const float DistanceFrom(const vec3& otherPos) const;
			const float DistanceFrom(const TransformComponent& other) const;
		};

	}
}
