#include "SpotLight.hpp"
#include "MaterialShaderStructs.hpp"
#include "MaterialShaderStructs.hpp"

using Bones::Lights::SpotLight;

SpotLight::SpotLight()
	: PointLight()
{
}

SpotLight::SpotLight(vec3 color, vec3 position, vec3 direction, float exponent, float linear, float constant)
	: PointLight(color, position, exponent, linear, constant, { 1024, 1024 }, { 0.01f, 100.0f }), m_direction(direction)
{
}
void SpotLight::MoveAndPoint(vec3 position, vec3 direction)
{
	m_position = position;
	m_direction = direction;
}
//
//void SpotLight::UseLight(GLint directionLocation, GLint cutOffLocation, GLint colorLocation, GLint positionLocation, GLint quadtraticLocation, GLint linearLocation, GLint constantLocation)
//{
//	PointLight::UseLight(colorLocation, positionLocation, quadtraticLocation, linearLocation, constantLocation);
//	glUniform3f(directionLocation, m_direction.x, m_direction.y, m_direction.z);
//	glUniform1f(cutOffLocation, m_edge);
//}

void SpotLight::UseLight(const SpotLightLocations& locations)
{
	PointLight::UseLight(locations);
	glUniform3f(locations.directionLocation, m_direction.x, m_direction.y, m_direction.z);
	glUniform1f(locations.cutOffLocation, m_cutOff);
	glUniform1f(locations.outerCutOffLocation, m_outerCutOff);
}
