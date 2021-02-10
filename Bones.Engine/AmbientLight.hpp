#pragma once

#include "BaseLight.hpp"

using namespace Bones::Light;
using glm::vec3;

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
	namespace Lights
	{
		class AmbientLight : public BaseLight
		{
		public:
			AmbientLight();
			AmbientLight(vec3 color);
			AmbientLight(vec3 color, float intensity);
			void UseLight(GLint colorLocation) const;
			void UseLight(const MaterialShader& shdr) const;
		};
	}
}

