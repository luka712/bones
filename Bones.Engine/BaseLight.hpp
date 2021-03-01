#pragma once

#include "core_types.h"
#include "vendor.h"
#include "glm/vec3.hpp"
#include "glm/ext.hpp"

using glm::vec3;

namespace Bones
{
	namespace Light
	{
		struct ShadowSize
		{
			unsigned int width;
			unsigned int height;
		};

		struct ProjectionNearFarPlane
		{
			float nearPlane;
			float farPlane;
		};

		/// <summary>
		/// The base light.
		/// </summary>
		class BaseLight
		{
		protected:
			BaseLight();
			BaseLight(vec3 color);
			BaseLight(vec3 color, float intensity);

			void UseLight(GLint colorLocation) const;

		public:
			vec3 m_color = vec3(1, 1, 1);
			float m_intensity = 1.0f, m_specularIntensity = 1.0f;

			virtual void Initialize();

			virtual ~BaseLight();
		};

	}
}