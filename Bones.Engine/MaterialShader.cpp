#include "MaterialShader.hpp"
#include <iostream>

using Bones::Shaders::Material::MaterialShader;

MaterialShader::MaterialShader(MaterialShaderOptions options)
	:m_options(options.ConvertToUL())
{
	Load();
}

MaterialShader::MaterialShader(unsigned long opts)
	:m_options(opts)
{
	Load();
}

void MaterialShader::Initialize()
{
	// do not inialize again if initalized already.
	if (m_initialized) return;

	BaseShader::Initialize();

	UseProgram();

	// transform
	m_transformLocation = GetUniformLocation("u_transform");

	// set camera
	m_cameraLocations.viewMatrixLocation = GetUniformLocation("u_view");
	m_cameraLocations.projectionMatrixLocation = GetUniformLocation("u_projection");
	// TODO: check what satisfies this condition
		
	if (!(MATERIAL_SHADER_DISABLE_LIGHTS & m_options) || (MATERIAL_SHADER_USE_REFLECTION_MAP & m_options))
	{
		m_cameraLocations.eyePositionLocation = GetUniformLocation("u_eyePosition");
	}

	// set material
	if (MATERIAL_SHADER_USE_DIFFUSE_MAP & m_options)
	{
		m_materialLocations.diffuseMapLocation = GetUniformLocation("u_material.diffuseMap");
	}
	else
	{
		m_materialLocations.diffuseColorLocation = GetUniformLocation("u_material.diffuseColor");
	}

	if (MATERIAL_SHADER_USE_SPECULAR_MAP & m_options)
	{
		m_materialLocations.specularMapLocation = GetUniformLocation("u_material.specularMap");
	}

	if (MATERIAL_SHADER_USE_REFLECTION_MAP & m_options)
	{
		m_materialLocations.reflectionMapLocation = GetUniformLocation("u_material.reflectionMap");
	}

	// TODO: check what satisfies this condition
	if (!(MATERIAL_SHADER_DISABLE_LIGHTS & m_options))
	{
		m_materialLocations.specularIntensityLocation = GetUniformLocation("u_material.intensity");
		m_materialLocations.specularShininessLocation = GetUniformLocation("u_material.shininess");
	}

	if (MATERIAL_SHADER_DISABLE_LIGHTS & m_options) return;


	// ambient light locations
	m_ambientLightLocations.colorLocation = GetUniformLocation("u_ambientLight.color");

	// directional light locations
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "u_directionalLights[%zu].base.color", i);
		m_directionalLightLocations[i].colorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_directionalLights[%zu].direction", i);
		m_directionalLightLocations[i].directionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_directionalLights[%zu].specularColor", i);
		m_directionalLightLocations[i].specularColorLocation = GetUniformLocation(locBuff);
	}
	m_directionalLightCountLocation = GetUniformLocation("u_directionalLightsCount");

	//m_directionalLightLocations.colorLocation = GetUniformLocation("u_directionalLight.base.color");
	//m_directionalLightLocations.intensityLocation = GetUniformLocation("u_directionalLight.base.intensity");
	//m_directionalLightLocations.directionLocation = GetUniformLocation("u_directionalLight.direction");
	//// TODO: move to struct from shader
	//m_directionalLightLocations.projectionViewLocation = GetUniformLocation("u_directionalLightProjView");
	//m_directionalLightLocations.shadowMapTextureLocation = GetUniformLocation("u_directionalShadowMapTex");

	// point lights locations
	for (size_t i = 0; i < MAX_POINT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].base.base.color", i);
		m_pointLightsLocations[i].colorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].base.specularColor", i);
		m_pointLightsLocations[i].specularColorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].position", i);
		m_pointLightsLocations[i].positionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].quadtratic", i);
		m_pointLightsLocations[i].attenuation.quadtraticLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].linear", i);
		m_pointLightsLocations[i].attenuation.linearLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_pointLights[%zu].constant", i);
		m_pointLightsLocations[i].attenuation.constantLocation = GetUniformLocation(locBuff);

		/*	snprintf(locBuff, sizeof(locBuff), "u_omniShadowMaps[%zu].farPlane", i);
			m_pointLightsLocations[i].farPlaneLocation = GetUniformLocation(locBuff);

			snprintf(locBuff, sizeof(locBuff), "u_omniShadowMaps[%zu].shadowMap", i);
			m_pointLightsLocations[i].shadowMapLocation = GetUniformLocation(locBuff);*/
	}
	m_pointLightsCountLocation = GetUniformLocation("u_pointLightsCount");

	// spot lights locations
	for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	{
		char locBuff[100] = { '\0' };

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.base.color", i);
		m_spotLightsLocations[i].colorLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.position", i);
		m_spotLightsLocations[i].positionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.quadtratic", i);
		m_spotLightsLocations[i].attenuation.quadtraticLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.linear", i);
		m_spotLightsLocations[i].attenuation.linearLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.constant", i);
		m_spotLightsLocations[i].attenuation.constantLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.direction", i);
		m_spotLightsLocations[i].directionLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].cutOff", i);
		m_spotLightsLocations[i].cutOffLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].outerCutOff", i);
		m_spotLightsLocations[i].outerCutOffLocation = GetUniformLocation(locBuff);

		/*		snprintf(locBuff, sizeof(locBuff), "u_omniShadowMaps[%zu].farPlane", i);
		m_spotLightsLocations[i].farPlaneLocation = GetUniformLocation(locBuff);

		snprintf(locBuff, sizeof(locBuff), "u_omniShadowMaps[%zu].shadowMap", i);
		m_spotLightsLocations[i].shadowMapLocation = GetUniformLocation(locBuff);*/
	}
	m_spotLightsCountLocation = GetUniformLocation("u_spotLightsCount");


	//// spot lights locations
	//for (size_t i = 0; i < MAX_SPOT_LIGHTS; i++)
	//{
	//	char locBuff[100] = { '\0' };

	//	snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.color", i);
	//	m_spotLightsLocations.spotLightLocations[i].colorLocation = GetUniformLocation(locBuff);

	//	snprintf(locBuff, sizeof(locBuff), "u_spotLights[%zu].base.base.intensity", i);
	//	m_spotLightsLocations.spotLightLocations[i].intensityLocation = GetUniformLocation(locBuff);
	//}
}

void MaterialShader::Load()
{
	map<string, int> shaderOptionsMap =
	{
		{ "##DIFFUSE_MAP##", (m_options & MATERIAL_SHADER_USE_DIFFUSE_MAP) != 0},
		{ "##SPECULAR_MAP##", (m_options & MATERIAL_SHADER_USE_SPECULAR_MAP) != 0},
		{ "##REFLECTION_MAP##", (m_options & MATERIAL_SHADER_USE_REFLECTION_MAP) != 0},
		{ "##USE_LIGHTS##", (m_options & MATERIAL_SHADER_DISABLE_LIGHTS) == 0 },
		{ "##MAX_DIRECTIONAL_LIGHTS##", MAX_DIRECTIONAL_LIGHTS },
		{ "##MAX_POINT_LIGHTS##", MAX_POINT_LIGHTS},
		{ "##MAX_SPOT_LIGHTS##", MAX_SPOT_LIGHTS},
	};

	ShaderSourceData source = ShaderParser().LoadFromFile(string(MATERIAL_SHADERS_PATH) + "NoShadow_MaterialShader" + SHADER_SUFFIX, shaderOptionsMap);

	/*else
	{
		source = ShaderParser().LoadFromFile(string(MATERIAL_SHADERS_PATH) + "MaterialShader" + SHADER_SUFFIX);
	}*/
	m_vertexSource = source.vertexSource;
	m_fragmentSource = source.fragmentSource;
}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;

EMSCRIPTEN_BINDINGS(MaterialShader_JS)
{
	class_<MaterialShader, base<BaseShader>>("MaterialShader")
		.constructor();
}

#endif 
