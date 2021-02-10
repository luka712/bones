#include "BaseCamera.hpp"
#include "MaterialShader.hpp"

using namespace Bones::Camera;
using Bones::Shaders::Material::MaterialShader;

BaseCamera::BaseCamera()
{
	m_transform = new TransformComponent();
	m_controls = nullptr;
	vec3 pos = vec3(0.0f, 0.0f, 4.0f);
	vec3 lookAt = vec3(0.0f, 0.0f, -1.0f);
	m_viewMatrix = glm::lookAt(pos, vec3(0,0,0), m_worldUp);
	m_projectionMatrix = perspective(radians(m_fov), m_width / m_height, m_near, m_far);
}

BaseCamera::BaseCamera(mat4 viewMatrix, mat4 projectionMatrix) : BaseCamera()
{
	m_viewMatrix = viewMatrix; 
	m_projectionMatrix = projectionMatrix;
	m_controls = nullptr;
}

BaseCamera::~BaseCamera()
{
	if (m_transform != nullptr)
	{
		delete m_transform;
		m_transform = nullptr;
	}
	if (m_controls != nullptr)
	{
		delete m_controls;
		m_controls = nullptr;
	}

}

void BaseCamera::UseCamera(GLint projectionLocation, GLint viewLocation, GLint posLocation) const
{
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, value_ptr(this->m_projectionMatrix));
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, value_ptr(this->m_viewMatrix));
	auto& pos = m_transform->GetPosition();
	glUniform3f(posLocation, pos.x, pos.y, pos.z);
}

void BaseCamera::UseCamera(const MaterialShader& shdr) const
{
	UseCamera(shdr.m_cameraLocations.projectionMatrixLocation, shdr.m_cameraLocations.viewMatrixLocation, shdr.m_transformLocation);
}
