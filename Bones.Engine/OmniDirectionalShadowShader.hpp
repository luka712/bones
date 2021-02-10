#pragma once

#include <vector>
#include "BaseShader.hpp"
#include "ShaderParser.hpp"
#include "TransformComponent.hpp"

using namespace std;
using namespace glm;
using Bones::Shaders::BaseShader;

namespace Bones
{
	namespace Shader
	{
		class OmniDirectionalShadowShader : public BaseShader
		{
		protected:
			GLint m_transformLocation, m_omniDirectionalLightProjViewLocations[6],
				m_lightPosition, m_farPlane;
		public:
			OmniDirectionalShadowShader();

			// methods
			void Initialize() override;

			void UseTransform(const mat4& transform) ;
			void UseLightPosition(const vec3& position);
			void UseFarPlane(const float farPlane);
			void UseLightProjectionViewLocations(const mat4* lightProjections);
		};

	}
}