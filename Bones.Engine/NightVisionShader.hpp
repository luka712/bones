#pragma once 

#ifndef  NIGHT_VISION_SHADER_H

#define  NIGHT_VISION_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class NightVisionShader final : public BasePostProcessShader
			{
			public:
				int m_scaleLocation = -1, m_distortionLocation = -1, m_scanLineTileAmountLocation = -1,
					m_randomLocation = -1, m_timeLocation = -1,
					m_vignetteTextureLocation = -1, m_scanLineTextureLocation = -1, m_noiseTextureLocation = -1,
					m_brightnessLocation = -1, m_contrastLocation = -1,
					m_noiseSpeedLocation = -1, m_nightVisionColorLocation = -1,
					m_vignetteIntesity = -1, m_noiseIntensity = -1, m_scanLineIntensity = -1;
				  

				NightVisionShader();

				void Initialize() override;
			};
		}
	}
}

#endif // ! NIGHT_VISION_SHADER_H
