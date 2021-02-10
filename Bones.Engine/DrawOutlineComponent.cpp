#include "DrawOutlineComponent.hpp"
#include "SceneObject.hpp"
#include "ShaderManager.hpp"
#include "Scene.hpp"

using Bones::Managers::ShaderManager;
using Bones::Components::Draw::DrawOutlineComponent;
using Bones::Scene;

DrawOutlineComponent::DrawOutlineComponent(SceneObject* sceneObj)
{
	m_sceneObject = sceneObj;
	m_shader = nullptr;
}

DrawOutlineComponent::~DrawOutlineComponent()
{
	m_sceneObject = nullptr;
}

void DrawOutlineComponent::Initialize()
{
	if (m_initialized) return;

	m_initialized = true;

	m_shader = ShaderManager::GetOrCreateStencilOutlineShader();
	m_shader->Initialize();
}

void DrawOutlineComponent::Draw()
{
	TransformComponent transform = m_sceneObject->GetTransform();
	BaseCamera& camera = m_sceneObject->m_scene->GetActiveCamera();

	glm::mat4 tran = mat4(1.0f);
	tran = translate(tran, transform.m_position);
	//auto rotateX = glm::rotate(transform, rotation->x, glm::vec3(1.0f, 0.0f, 0.0f));
	//auto rotateY = glm::rotate(transform, rotation->y, glm::vec3(0.0f, 1.0f, 0.0f));
	//auto rotateZ = glm::rotate(transform, rotation->z, glm::vec3(0.0f, 0.0f, 1.0f));*/
	float scl = m_scaleFactor - 1.0f;
	tran = scale(tran, transform.m_scale + scl);
	m_shader->SetMatrix(m_shader->m_locations.transformLocation, tran);
	m_shader->SetMatrix(m_shader->m_locations.projectionLocation, camera.m_projectionMatrix);
	m_shader->SetMatrix(m_shader->m_locations.viewLocation, camera.m_viewMatrix);
	m_shader->SetFloat4(m_shader->m_locations.colorLocation, m_color);
	
}

