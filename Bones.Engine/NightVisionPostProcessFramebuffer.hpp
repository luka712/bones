#pragma once

#ifndef NIGHT_VISION_POST_PROCESS_FRAMEBUFFER_H

#define NIGHT_VISION_POST_PROCESS_FRAMEBUFFER_H

#include "PostProcessFramebuffer.hpp"
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"

namespace Bones
{
	namespace Textures
	{
		class Texture2D;
	}

	namespace Shaders
	{
		namespace PostProcess
		{
			class NightVisionShader;
		}
	}
}

using glm::vec2;
using glm::vec3;
using Bones::Textures::Texture2D;
using Bones::Shaders::PostProcess::NightVisionShader;

namespace Bones
{
	namespace Framebuffers
	{
		namespace PostProcess
		{
			/// <summary>
			/// The night vision post process framebuffer.
			/// </summary>
			class NightVisionPostProcessFramebuffer : public PostProcessFramebuffer
			{
			public:
				// various night vision options
				F32 m_scale = 0.8f,
					m_distortion = 0.2f;

				// ref to shader
				NightVisionShader* m_postProcessShader = nullptr;

				// used textures.
				Texture2D* m_vignetteTexture = nullptr,
					* m_noiseTexture = nullptr,
					* m_scanLineTexture = nullptr;
			
				// noise speed and night vision color.
				vec2 m_noiseSpeed = vec2(1, 1);
				vec3 m_nightVisionColor = vec3(0, 1, 0);
	
				/// <summary>
				/// The constructor
				/// </summary>
				/// <param name="shader">The night vision shader.</param>
				NightVisionPostProcessFramebuffer(NightVisionShader* shader);

				/// <summary>
				/// The noisy preset.
				/// </summary>
				void NoisyPreset();

				/// <summary>
				/// The preset with ligher noise.
				/// </summary>
				void LightNoisePreset();

				/// <summary>
				/// Noisy preset without vignette effect.
				/// </summary>
				void NoiseNoVignettePreset();

				/// <summary>
				/// Less noisy preset without vignette effect.
				/// </summary>
				void LightNoVignettePreset();
			private:
				// simple timer, used to pass time to shader.
				F32 m_timer;
			};
		}
	}
}

#endif // !NIGHT_VISION_POST_PROCESS_FRAMEBUFFER_H
