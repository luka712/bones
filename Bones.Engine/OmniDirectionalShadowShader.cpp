//#include "OmniDirectionalShadowShader.hpp"
//
//using namespace Bones::Shader;
//
//
//OmniDirectionalShadowShader::OmniDirectionalShadowShader()
//{
//	Bones::Loaders::ShaderSourceData source = Bones::Loaders::ShaderParser().LoadFromFile(string(SHADOW_SHADERS_PATH) + "OmniDirectionalShadowMap" + SHADER_SUFFIX);
//	m_vertexSource = source.vertexSource;
//	m_geometrySource = source.geometrySource;
//	m_fragmentSource = source.fragmentSource;
//}
//
//void OmniDirectionalShadowShader::Initialize()
//{
//	if (m_initialized) return;
//
//	BaseShader::Initialize();
//
//	m_transformLocation = GetUniformLocation("u_transform");
//	for (size_t i = 0; i < 6; i++)
//	{
//		char locBuff[100] = { '\0' };
//
//		snprintf(locBuff, sizeof(locBuff), "u_lightProjectionView[%zu]", i);
//		m_omniDirectionalLightProjViewLocations[i] = GetUniformLocation(locBuff);
//	}
//}
//
//void OmniDirectionalShadowShader::UseTransform(const mat4& transform)
//{
//	glUniformMatrix4fv(m_transformLocation, 1, GL_FALSE, value_ptr(transform));
//}
//
//void OmniDirectionalShadowShader::UseLightPosition(const vec3& position)
//{
//	glUniform3f(m_lightPosition, position.x, position.y, position.z);
//}
//
//void OmniDirectionalShadowShader::UseFarPlane(const float farPlane)
//{
//	glUniform1f(m_farPlane, farPlane);
//}
//
//void OmniDirectionalShadowShader::UseLightProjectionViewLocations(const mat4 *lightProjections)
//{
//	for (size_t i = 0; i < 6; i++)
//	{
//		glUniformMatrix4fv(m_omniDirectionalLightProjViewLocations[i], 1, GL_FALSE, value_ptr(lightProjections[i]));
//	}
//}
