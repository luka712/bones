#include "BaseLight.hpp"

using namespace Bones::Light;

BaseLight::BaseLight()
	: BaseLight(vec3(1,1,1), 0.1f)
{
}

BaseLight::BaseLight(vec3 color)
	: m_color(color)
{
}

BaseLight::BaseLight(vec3 color, float intensity)
	: BaseLight(color)
{
	m_intensity = intensity;
}

void BaseLight::UseLight(GLint colorLocation) const
{
	glUniform3f(colorLocation, m_color.r * m_intensity, m_color.g * m_intensity, m_color.b * m_intensity);
}

void BaseLight::Initialize()
{
}


BaseLight::~BaseLight()
{
}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(Light_JS)
{
}

#endif