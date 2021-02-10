#include "StencilOutlineShader.hpp"

using Bones::Shaders::Stencil::StencilOutlineShader;

StencilOutlineShader::StencilOutlineShader()
{
	Load();
}

void StencilOutlineShader::Load()
{
	ShaderSourceData source = ShaderParser().LoadFromFile(string(STENCIL_SHADERS_PATH) + "ColorOutline" + SHADER_SUFFIX);
	m_vertexSource = source.vertexSource;
	m_fragmentSource = source.fragmentSource;
}

void StencilOutlineShader::Initialize()
{
	// do not inialize again if initalized already.
	if (m_initialized) return;

	BaseShader::Initialize();

	UseProgram();

	m_locations.transformLocation = GetUniformLocation("u_transform");
	m_locations.viewLocation = GetUniformLocation("u_view");
	m_locations.projectionLocation = GetUniformLocation("u_projection");
	m_locations.colorLocation = GetUniformLocation("u_color");
}