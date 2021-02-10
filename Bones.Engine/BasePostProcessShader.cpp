#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;
using Bones::Shaders::BaseShader;

BasePostProcessShader::BasePostProcessShader()
{
	m_textureLocation = 0;
}

BasePostProcessShader::BasePostProcessShader(string vertexSource, string fragmentSource)
	:BasePostProcessShader()
{
	m_vertexSource = vertexSource;
	m_fragmentSource = fragmentSource;
}

void BasePostProcessShader::Initialize()
{
	BaseShader::Initialize();

	m_textureLocation = GetUniformLocation("u_screenTexture");
}
