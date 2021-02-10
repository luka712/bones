#include "SkyboxShader.hpp"
#include "BaseCamera.hpp"

using glm::mat3;
using glm::mat4;
using Bones::Shaders::Environment::SkyboxShader;

SkyboxShader::SkyboxShader()
{
	Load();
}

void SkyboxShader::Initialize()
{
	// do not inialize again if initalized already.
	if (m_initialized) return;

	BaseShader::Initialize();

	UseProgram();

	// set camera
	m_cameraLocations.viewMatrixLocation = GetUniformLocation("u_view");
	m_cameraLocations.projectionMatrixLocation = GetUniformLocation("u_projection");

	m_cubeTextureLocation = GetUniformLocation("u_texture");
}

void SkyboxShader::SetCameraLocations(const BaseCamera& camera)
{
	SetMatrix(m_cameraLocations.projectionMatrixLocation, camera.m_projectionMatrix);
	// get rid of transforms
	mat4 view = mat4(mat3(camera.m_viewMatrix));
	SetMatrix(m_cameraLocations.viewMatrixLocation, view);
}


void SkyboxShader::Load()
{
	ShaderSourceData source;

	map<string, int> shaderOptionsMap;

	source = ShaderParser().LoadFromFile(string(ENVIRONMENT_SHADERS_PATH) + "Skybox" + SHADER_SUFFIX, shaderOptionsMap);

	m_vertexSource = source.vertexSource;
	m_fragmentSource = source.fragmentSource;
}
