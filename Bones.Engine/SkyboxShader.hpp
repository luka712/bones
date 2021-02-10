#pragma once 

#ifndef SKYBOX_SHADER_H

#define SKYBOX_SHADER_H

/*
	1. Constructor
	2. Load
	3. Initialize
*/

#include "BaseShader.hpp"
#include "BaseShaderStructs.hpp"

using namespace std;
using namespace glm;
using namespace Bones::Loaders;

namespace Bones
{
	namespace Camera
	{
		class BaseCamera;
	}
}

using Bones::Shaders::BaseShader;
using Bones::Camera::BaseCamera;

namespace Bones
{
	namespace Shaders
	{
		namespace Environment
		{
			class SkyboxShader final : public BaseShader
			{
			public:
				unsigned int m_cubeTextureLocation;
				CameraLocations m_cameraLocations = {};

				SkyboxShader();

				void Load() override;
				void Initialize() override;

				void SetCameraLocations(const BaseCamera& camera);
			};
		}

	}
}

#endif // !SKYBOX_SHADER_H