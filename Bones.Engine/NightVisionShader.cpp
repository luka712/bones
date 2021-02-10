#include "NightVisionShader.hpp"

using Bones::Shaders::PostProcess::NightVisionShader;

NightVisionShader::NightVisionShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "NightVision" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}

void NightVisionShader::Initialize()
{
	BasePostProcessShader::Initialize();

	m_vignetteTextureLocation = GetUniformLocation("u_vignetteTexture");
	m_scanLineTextureLocation = GetUniformLocation("u_scanLineTexture");
	m_noiseTextureLocation = GetUniformLocation("u_noiseTexture");

	m_scaleLocation = GetUniformLocation("u_scale");
	m_distortionLocation = GetUniformLocation("u_distortion");
	m_scanLineTileAmountLocation = GetUniformLocation("u_scanLineTileAmount");
	m_timeLocation = GetUniformLocation("u_time");
	m_randomLocation = GetUniformLocation("u_random");
	m_contrastLocation = GetUniformLocation("u_contrast");
	m_brightnessLocation = GetUniformLocation("u_brightness");
	m_vignetteIntesity = GetUniformLocation("u_vignetteIntesity");
	m_noiseIntensity = GetUniformLocation("u_noiseIntensity");
	m_scanLineIntensity = GetUniformLocation("u_scanLineIntensity");

	m_noiseSpeedLocation = GetUniformLocation("u_noiseSpeed");
	m_nightVisionColorLocation = GetUniformLocation("u_nightVisionColor");
}
