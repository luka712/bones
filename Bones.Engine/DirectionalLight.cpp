#include "DirectionalLight.hpp"
#include "MaterialShaderStructs.hpp"

using namespace Bones::Light;
// using Bones::Textures::GLTextureUnit;

DirectionalLight::DirectionalLight()
	:DirectionalLight(vec3(1,0,1), vec3(1,1,1), .4f)
{
}

DirectionalLight::DirectionalLight(vec3 direction, vec3 color)
	: DirectionalLight(direction, color, 1.f)
{
	
}

DirectionalLight::DirectionalLight(vec3 direction, vec3 color, float intensity)
	:BaseLight(color, intensity)
{
	m_direction = direction;
	// m_shadowMap = new DirectionalLightShadowMap();
	m_specularColor = vec3(0.75f, 0.75f, 0.75f);
	m_projection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.1f, 20.0f);
	m_view = glm::lookAt(-m_direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	m_projectionView = m_projection * m_view;
}

void DirectionalLight::Initialize()
{
	// m_shadowMap->Initialize();
}

//void DirectionalLight::ReadShadowMap(GLTextureUnit textureUnit, unsigned int offset) const
//{
//	m_shadowMap->Read(textureUnit, offset);
//}

//void DirectionalLight::ReadShadowMap(GLTextureUnit textureUnit) const
//{
//	m_shadowMap->Read(textureUnit);
//}

void DirectionalLight::UseLight(const DirectionalLightLocations& locations)
{
	BaseLight::UseLight(locations.colorLocation);
	glUniform3f(locations.specularColorLocation, m_specularColor.x * m_specularIntensity, m_specularColor.y * m_specularIntensity, m_specularColor.z * m_specularIntensity);
	glUniform3f(locations.directionLocation, m_direction.x, m_direction.y, m_direction.z);
	// sglUniformMatrix4fv(locations.projectionViewLocation, 1, GL_FALSE, value_ptr(m_projectionView));
}


void DirectionalLight::SetDirection(float x, float y, float z)
{
	m_direction.x = x;
	m_direction.y = y;
	m_direction.z = z;
}

DirectionalLight::~DirectionalLight()
{
	// delete m_shadowMap;
	// m_shadowMap = nullptr;
}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(DirectionalLight_JS)
{
	
}

#endif