#include "NoShadowsMaterialShader.hpp"
#include <iostream>
#include <stdio.h>

using namespace Bones::Shader;

NoShadowsMaterialShader::NoShadowsMaterialShader()
{
	ShaderSourceData source = ShaderParser().LoadFromFile(string(MATERIAL_SHADERS_PATH) + "NoShadow_MaterialShader" + SHADER_SUFFIX);
	m_vertexSource = source.vertexSource;
	m_fragmentSource = source.fragmentSource;
}

void NoShadowsMaterialShader::Initialize()
{
	// do not inialize again if initalized already.
	if (m_initialized) return;

	BaseShader::Initialize();

	// transform
	m_transformLocation = GetUniformLocation("u_transform");

	// set material
	m_materialLocations.specularIntensityLocation = GetUniformLocation("u_material.intensity");
	m_materialLocations.specularShininessLocation = GetUniformLocation("u_material.shininess");

	// set camera
	m_cameraLocations.viewMatrixLocation = GetUniformLocation("u_view");
	m_cameraLocations.projectionMatrixLocation = GetUniformLocation("u_projection");
	m_cameraLocations.eyePositionLocation = GetUniformLocation("u_eyePosition");

	// ambient light locations
	m_ambientLightLocations.colorLocation = GetUniformLocation("u_ambientLight.base.color");
	m_ambientLightLocations.intensityLocation = GetUniformLocation("u_ambientLight.base.intensity");

	// directional light locations
	m_directionalLightLocations.colorLocation = GetUniformLocation("u_directionalLight.base.color");
	m_directionalLightLocations.intensityLocation = GetUniformLocation("u_directionalLight.base.intensity");
	m_directionalLightLocations.directionLocation = GetUniformLocation("u_directionalLight.direction");
	// TODO: move to struct from shader
	m_directionalLightLocations.projectionViewLocation = GetUniformLocation("u_directionalLightProjView");

	// point lights locations
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].base.color", i);
		m_pointLightsLocations.pointLightLocations[i].colorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].base.intensity", i);
		m_pointLightsLocations.pointLightLocations[i].intensityLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].position", i);
		m_pointLightsLocations.pointLightLocations[i].positionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].exponent", i);
		m_pointLightsLocations.pointLightLocations[i].attenuation.exponentLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].linear", i);
		m_pointLightsLocations.pointLightLocations[i].attenuation.linearLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].constant", i);
		m_pointLightsLocations.pointLightLocations[i].attenuation.constantLocation = GetUniformLocation(locBuff);
	}
	m_pointLightsLocations.pointLightsCountLocation = GetUniformLocation("u_pointLightsCount");

	// spot lights locations
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.color", i);
		m_spotLightsLocations.spotLightLocations[i].colorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.intensity", i);
		m_spotLightsLocations.spotLightLocations[i].intensityLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.position", i);
		m_spotLightsLocations.spotLightLocations[i].positionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.exponent", i);
		m_spotLightsLocations.spotLightLocations[i].attenuation.exponentLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.linear", i);
		m_spotLightsLocations.spotLightLocations[i].attenuation.linearLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.constant", i);
		m_spotLightsLocations.spotLightLocations[i].attenuation.constantLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].direction", i);
		m_spotLightsLocations.spotLightLocations[i].directionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].edge", i);
		m_spotLightsLocations.spotLightLocations[i].cutOffLocation = GetUniformLocation(locBuff);
	}
	m_spotLightsLocations.spotLightsCountLocation = GetUniformLocation("u_spotLightsCount");


	// spot lights locations
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.color", i);
		m_spotLightsLocations.spotLightLocations[i].colorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.intensity", i);
		m_spotLightsLocations.spotLightLocations[i].intensityLocation = GetUniformLocation(locBuff);
	}

}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;

EMSCRIPTEN_BINDINGS(MaterialShader_JS)
{
	class_<MaterialShader, base<BaseShader>>("MaterialShader")
		.constructor();
}

#endif 
