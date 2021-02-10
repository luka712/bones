//#include "DirectionalShadowShader.hpp"
//
//using Bones::Shaders::BaseShader;
//using Bones::Shader::DirectionalShadowShader;
//
//DirectionalShadowShader::DirectionalShadowShader()
//{
//	ShaderSourceData source = ShaderParser().LoadFromFile(string(SHADOW_SHADERS_PATH) + "DirectionalShadowMap" + SHADER_SUFFIX);
//	m_vertexSource = source.vertexSource;
//	m_fragmentSource = source.fragmentSource;
//}
//
//void DirectionalShadowShader::Initialize()
//{
//	if (m_initialized) return;
//
//	BaseShader::Initialize();
//
//	m_transformLocation = GetUniformLocation("u_transform");
//	m_directionalLightProjViewLocation = GetUniformLocation("u_directionalLightProjView");
//}
//
//void DirectionalShadowShader::UseTransform(const mat4& transform)
//{
//	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, value_ptr(transform));
//}
//
//void DirectionalShadowShader::UseLightProjectionViewLocation(const mat4& lightProjView)
//{
//	glUniformMatrix4fv(m_directionalLightProjViewLocation, 1, GL_FALSE, value_ptr(lightProjView));
//}
