#include "PointLight.hpp"
#include "MaterialShader.hpp"
#include "MaterialShaderStructs.hpp"


// TODO: refactor Attenuation.
PointLight::PointLight(vec3 color,vec3 position, float exponent, float linear, float constant, ShadowSize shadowSize, ProjectionNearFarPlane projectionPlane)
	: BaseLight(color), m_position(position), m_quadtratic(exponent), m_linear(linear), m_constant(constant), m_shadowSize(shadowSize), m_projectionPlane(projectionPlane)
{
	m_intensity = 5.f;
	m_specularIntensity = 10.f;
	float aspect = (float)shadowSize.width / (float)shadowSize.height;
	m_specularColor = color;
	m_projection = perspective(radians(90.0f), aspect, projectionPlane.nearPlane, projectionPlane.farPlane);

	// RefreshShadowProjectionMatrices();
	// m_shadowMap = new OmniDirectionalLightShadowMap();
}


PointLight::PointLight()
	: PointLight(vec3(1, 1, 1), vec3(0, 0, 0), 0.07f, 0.14f, 1.0f, { 1024, 1024 }, { 0.01f, 100.0f })
{}

PointLight::PointLight(vec3 position)
	: PointLight(vec3(1, 1, 1), position, 0.07f, 0.14f, 1.0f, { 1024, 1024 }, { 0.01f, 100.0f })
{}

PointLight::PointLight(vec3 position, vec3 color)
	:PointLight(color, position, 0.07f, 0.14f, 1.0f, { 1024, 1024 }, { 0.01f, 100.0f })
{
}

void Bones::Light::PointLight::Initialize()
{
	/*if (m_shadowMap != nullptr)
	{
		m_shadowMap->Initialize();
	}*/
}

void PointLight::RefreshShadowProjectionMatrices() noexcept
{
	m_view[0] = lookAt(m_position, m_position + vec3(1, 0, 0), vec3(0, -1, 0));
	m_view[1] = lookAt(m_position, m_position + vec3(-1, 0, 0), vec3(0, -1, 0));
	m_view[2] = lookAt(m_position, m_position + vec3(0, 1, 0), vec3(0, 0, 1));
	m_view[3] = lookAt(m_position, m_position + vec3(0, -1, 0), vec3(0, 0, -1));
	m_view[4] = lookAt(m_position, m_position + vec3(0, 0, 1), vec3(0, -1, 0));
	m_view[5] = lookAt(m_position, m_position + vec3(0, 0, -1), vec3(0, -1, 0));

	for (int i = 0; i < 6; i++)
	{
		m_projectionView[i] = m_projection * m_view[i];
	}
}


//void PointLight::ReadShadowMap(GLTextureUnit textureUnit, unsigned int offset) const
//{
//	m_shadowMap->Read(textureUnit, offset);
//}
//
//void Bones::Light::PointLight::ReadShadowMap(GLenum textureUnit, unsigned int offset) const
//{
//	m_shadowMap->Read(textureUnit, offset);
//}

void PointLight::UseLight(const PointLightLocations& pointLightLocations)
{
	BaseLight::UseLight(pointLightLocations.colorLocation);
	glUniform3f(pointLightLocations.positionLocation, m_position.x, m_position.y, m_position.z);
	glUniform4f(pointLightLocations.specularColorLocation, m_specularColor.x * m_specularIntensity, m_specularColor.y * m_specularIntensity, m_specularColor.z * m_specularIntensity, m_specularColor.z * m_specularIntensity);
	glUniform1f(pointLightLocations.attenuation.quadtraticLocation, m_quadtratic);
	glUniform1f(pointLightLocations.attenuation.linearLocation, m_linear);
	glUniform1f(pointLightLocations.attenuation.constantLocation, m_constant);
	// glUniform1f(pointLightLocations.farPlaneLocation, m_projectionPlane.far);
}

void PointLight::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;
	RefreshShadowProjectionMatrices();
}

void PointLight::SetAttenuation(float constant, float linear, float exponent)
{
	m_constant = constant;
	m_linear = linear;
	m_quadtratic = exponent;
}


#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(PointLight_JS)
{
	
}

#endif