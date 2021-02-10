#pragma once 

#ifndef MATERIALSHADER_H

#define MATERIALSHADER_H

/*
	1. Constructor
	2. Load
	3. Initialize
*/

#include "BaseShader.hpp"
#include "BaseShaderStructs.hpp"
#include "MaterialShaderStructs.hpp"

using namespace std;
using namespace glm;
using namespace Bones::Loaders;

using Bones::Shaders::BaseShader;

namespace Bones
{
	namespace Shaders
	{
		namespace Material
		{
			class MaterialShader final : public BaseShader
			{
			public:
				// options
				material_shader_options m_options;

				// transform camera locations
				GLint m_transformLocation = -1;
				MaterialLocations m_materialLocations = {};
				CameraLocations m_cameraLocations = {};

				// light locations
				AmbientLightLocations m_ambientLightLocations = {};
				DirectionalLightLocations m_directionalLightLocations[MAX_DIRECTIONAL_LIGHTS];
				GLint m_directionalLightCountLocation = -1;
				PointLightLocations m_pointLightsLocations[MAX_POINT_LIGHTS];
				GLint m_pointLightsCountLocation = -1;
				SpotLightLocations m_spotLightsLocations[MAX_DIRECTIONAL_LIGHTS];
				GLint m_spotLightsCountLocation = -1;

				MaterialShader(MaterialShaderOptions opts);
				MaterialShader(material_shader_options opts = 0);

#pragma region Framework Methods
				void Load() override;
				void Initialize() override;
#pragma endregion

			};
		}

	}
}

#endif // !MATERIALSHADER_H