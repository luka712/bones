#pragma once

#include "PointLight.hpp"

namespace Bones
{
	namespace Shaders
	{
		namespace Material
		{
			struct SpotLightLocations;
		}
	}
}

using Bones::Shaders::Material::SpotLightLocations;

namespace Bones
{
	namespace Lights
	{
		class SpotLight : public PointLight
		{
		private:
			vec3 m_direction;
			float m_cutOff = cos(radians(10.0f)),
				m_outerCutOff = cos(radians(17.5f));
		public:
			SpotLight();
			SpotLight(vec3 color, vec3 position, vec3 direction, float exponent, float linear, float constant);

			/*void UseLight(GLint directionLocation, GLint cutOffLocation, GLint colorLocation,
				 GLint positionLocation, GLint quadtraticLocation, GLint linearLocation, GLint constantLocation);*/

				 // TODO: Use transform component instead.
			void MoveAndPoint(vec3 position, vec3 direction);

			void UseLight(const SpotLightLocations& locations);
		};

	}
}
