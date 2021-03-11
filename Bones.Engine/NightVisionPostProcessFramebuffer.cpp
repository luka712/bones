#include "NightVisionPostProcessFramebuffer.hpp"
#include "TextureManager.hpp"
#include "Texture2D.hpp"
#include "NightVisionShader.hpp"
#include "core_types.h"

using Bones::Framebuffers::PostProcess::NightVisionPostProcessFramebuffer;
using Bones::Managers::TextureManager;

NightVisionPostProcessFramebuffer::NightVisionPostProcessFramebuffer(NightVisionShader* shader)
	:m_postProcessShader(shader), PostProcessFramebuffer(shader)
{
	m_onLoad = [&]() -> void
	{
		// TODO Make it async
		m_vignetteTexture = TextureManager::GetOrCreateTexture2D("resources/textures/postprocess/vignette.png");
		m_noiseTexture = TextureManager::GetOrCreateTexture2D("resources/textures/postprocess/noise.png");
		m_scanLineTexture = TextureManager::GetOrCreateTexture2D("resources/textures/postprocess/scanline.png");
	};

	m_onInitialized = [&]() -> void
	{
		// barrel effect
		AddValue("u_distortion", 0.2f, ValueType::FLOAT, "distortion");
		AddValue("u_scale", 0.8f, ValueType::FLOAT, "scale");

		// contrast, brightness 
		AddValue("u_brightness", 0.1f, ValueType::FLOAT, "brightness");
		AddValue("u_contrast", 3.0f, ValueType::FLOAT, "contrast");

		// scanlines size
		AddValue("u_scanLineTileAmount", 4.0f, ValueType::FLOAT, "scanline tiles amount");

		// intensities
		AddValue("u_vignetteIntensity", 1.0f, ValueType::FLOAT, "vignette intensity");
		AddValue("u_noiseIntensity", 1.0f, ValueType::FLOAT, "noise intensity");
		AddValue("u_scanLineIntensity", 1.0f, ValueType::FLOAT, "scanline intensity");

		AddValue("u_noiseSpeed", (1.0f, 1.0f), ValueType::VEC2, "noise speed");

		LightNoVignettePreset();
	};

	m_onBindUniforms = [&]() -> void
	{
		// TODO : to update
		m_timer += 0.001f;

		auto& shader = *m_postProcessShader;

		// textures
		shader.SetTexture(shader.m_vignetteTextureLocation, 1);
		shader.SetTexture(shader.m_scanLineTextureLocation, 2);
		shader.SetTexture(shader.m_noiseTextureLocation, 3);


		

#if EMSCRIPTEN_RUNTIME
		shader.SetFloat(shader.m_randomLocation, (emscripten_random() - 0.5f) * 2.0f);
#else 
		shader.SetFloat(shader.m_randomLocation, (rand() - 0.5f) * 2.0f);
#endif 
		shader.SetFloat(shader.m_timeLocation, m_timer);


		shader.SetFloat3(shader.m_nightVisionColorLocation, m_nightVisionColor);

		for (auto& pair : m_values)
		{
			PostProcessFramebufferValue& val = pair.second;
			if (val.m_type == ValueType::FLOAT)
			{
				shader.SetFloat(val.m_locationId, val.m_value.m_asFloat);
			}
			else if (val.m_type == ValueType::VEC2)
			{
				shader.SetFloat2(val.m_locationId, val.m_value.m_asFloat2[0], val.m_value.m_asFloat2[1]);
			}
		}

		// bind textures
		m_vignetteTexture->BindTexture(1);
		m_scanLineTexture->BindTexture(2);
		m_noiseTexture->BindTexture(3);
	};
}


void NightVisionPostProcessFramebuffer::NoisyPreset()
{
	m_values.at("contrast").m_value.m_asFloat = 3.0f;
	m_values.at("brightness").m_value.m_asFloat  = 0.125f;
	m_values.at("vignette intensity").m_value.m_asFloat = 0.975f;
	m_values.at("noise intensity").m_value.m_asFloat = 1.0f;
	m_values.at("scanline intensity").m_value.m_asFloat = 1.0f;
}

void NightVisionPostProcessFramebuffer::LightNoisePreset()
{
	m_values.at("contrast").m_value.m_asFloat = 1.0f;
	m_values.at("brightness").m_value.m_asFloat = 0.1f;
	m_values.at("vignette intensity").m_value.m_asFloat = 0.9f;
	m_values.at("noise intensity").m_value.m_asFloat = 0.4f;
	m_values.at("scanline intensity").m_value.m_asFloat = 0.4f;
}

void NightVisionPostProcessFramebuffer::NoiseNoVignettePreset()
{
	NoisyPreset();
	m_values.at("vignette intensity").m_value.m_asFloat = 0.0f;
}
void NightVisionPostProcessFramebuffer::LightNoVignettePreset()
{
	m_values.at("contrast").m_value.m_asFloat = 0.5f;
	m_values.at("brightness").m_value.m_asFloat = 0.1f;
	m_values.at("noise intensity").m_value.m_asFloat = 0.1f;
	m_values.at("scanline intensity").m_value.m_asFloat = 0.1f;
	m_values.at("vignette intensity").m_value.m_asFloat = 0.0f;
}




