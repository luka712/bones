#include "NightVisionPostProcessFramebuffer.hpp"
#include "TextureManager.hpp"
#include "Texture2D.hpp"
#include "NightVisionShader.hpp"
#include "core_types.h"

using Bones::Framebuffers::PostProcess::NightVisionPostProcessFramebuffer;
using Bones::Managers::TextureManager;

NightVisionPostProcessFramebuffer::NightVisionPostProcessFramebuffer(NightVisionShader* shader)
	:PostProcessFramebuffer(shader)
{
	m_postProcessShader = shader;
	LightNoVignettePreset();
}

void NightVisionPostProcessFramebuffer::Load()
{
	m_vignetteTexture = TextureManager::GetOrCreateTexture2D("resources/textures/postprocess/vignette.png");
	m_noiseTexture = TextureManager::GetOrCreateTexture2D("resources/textures/postprocess/noise.png");
	m_scanLineTexture = TextureManager::GetOrCreateTexture2D("resources/textures/postprocess/scanline.png");
}

void NightVisionPostProcessFramebuffer::BindUniforms()
{
	// TODO : to update
	m_timer += 0.001f;

	// textures
	m_postProcessShader->SetTexture(m_postProcessShader->m_vignetteTextureLocation, 1);
	m_postProcessShader->SetTexture(m_postProcessShader->m_scanLineTextureLocation, 2);
    m_postProcessShader->SetTexture(m_postProcessShader->m_noiseTextureLocation, 3);

	// barrel effect
	m_postProcessShader->SetFloat(m_postProcessShader->m_distortionLocation, m_distortion);
	m_postProcessShader->SetFloat(m_postProcessShader->m_scaleLocation, m_scale);

	// scanlines size
	m_postProcessShader->SetFloat(m_postProcessShader->m_scanLineTileAmountLocation, m_scanLineTileAmount);

	// contrast, brightness
	m_postProcessShader->SetFloat(m_postProcessShader->m_brightnessLocation, m_brightness);
	m_postProcessShader->SetFloat(m_postProcessShader->m_contrastLocation, m_contrast);

	// intensities
	m_postProcessShader->SetFloat(m_postProcessShader->m_vignetteIntesity, m_vignetteIntensity);
	m_postProcessShader->SetFloat(m_postProcessShader->m_noiseIntensity, m_noiseIntensity);
	m_postProcessShader->SetFloat(m_postProcessShader->m_scanLineIntensity, m_scanLineInensity);

#if EMSCRIPTEN_RUNTIME
	m_postProcessShader->SetFloat(m_postProcessShader->m_randomLocation, (emscripten_random() - 0.5f) * 2.0f);
#else 
	m_postProcessShader->SetFloat(m_postProcessShader->m_randomLocation, (rand() - 0.5f) * 2.0f);
#endif 
	m_postProcessShader->SetFloat(m_postProcessShader->m_timeLocation, m_timer);

	m_postProcessShader->SetFloat2(m_postProcessShader->m_noiseSpeedLocation, m_noiseSpeed);
	m_postProcessShader->SetFloat3(m_postProcessShader->m_nightVisionColorLocation, m_nightVisionColor);

	// bind textures
	m_vignetteTexture->BindTexture(1);
	m_scanLineTexture->BindTexture(2);
	m_noiseTexture->BindTexture(3);
	
}

void NightVisionPostProcessFramebuffer::NoisyPreset()
{
	m_contrast = 3.0f;
	m_brightness = 0.125f;
	m_vignetteIntensity = 0.975f;
	m_noiseIntensity = 1.0f;
	m_scanLineInensity = 1.0f;
}

void NightVisionPostProcessFramebuffer::LightNoisePreset()
{
	m_contrast = 1;
	m_brightness = 0.1f;
	m_vignetteIntensity = 0.9f;
	m_noiseIntensity = 0.4f;
	m_scanLineInensity = 0.4f;
}

void NightVisionPostProcessFramebuffer::NoiseNoVignettePreset()
{
	NoisyPreset();
	m_vignetteIntensity = 0.0f;
}
void NightVisionPostProcessFramebuffer::LightNoVignettePreset()
{
	m_contrast = 0.5f;
	m_brightness = 0.1f;
	m_noiseIntensity = 0.1f;
	m_scanLineInensity = 0.1f;
	m_vignetteIntensity = 0.0f;
}




