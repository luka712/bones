#pragma once

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
		class DirectionalShadowShader : public BaseShader
		{
		protected:
			GLint m_transformLocation, m_directionalLightProjViewLocation;
		public:
			DirectionalShadowShader();

			// methods
			void Initialize() override;

			void UseTransform(const mat4& transform);
			void UseLightProjectionViewLocation(const mat4& lightProjection);
		};

	}
}
