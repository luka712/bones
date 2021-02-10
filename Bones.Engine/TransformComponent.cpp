#include "TransformComponent.hpp"

using namespace Bones::Component;

TransformComponent::TransformComponent()
{
	m_position = vec3(0, 0, 0);
	m_transform = mat4(1.0f);
	m_rotation = vec3(0, 0, 0);
	m_scale = vec3(1.0f, 1.0f, 1.0f);
}

TransformComponent& TransformComponent::SetPosition(const vec3& pos)
{
	m_position = pos; 

	return *this;
}

TransformComponent& TransformComponent::SetPosition(float x, float y, float z)
{
	m_position.x = x;
	m_position.y = y;
	m_position.z = z;

	return *this;
}

TransformComponent& TransformComponent::SetScale(const vec3& scale)
{
	m_scale = scale;

	return *this;
}

TransformComponent& TransformComponent::SetScale(float x, float y, float z)
{
	m_scale.x = x;
	m_scale.y = y;
	m_scale.z = y;

	return *this;
}

void TransformComponent::Update()
{
	m_transform = mat4(1.0f);
	m_transform = translate(m_transform, m_position);
	m_transform = rotate(m_transform, m_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	m_transform = rotate(m_transform, m_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	m_transform = rotate(m_transform, m_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	m_transform = scale(m_transform, m_scale);
}

void TransformComponent::UseTransform(GLint transformLocation) const
{
	glUniformMatrix4fv(transformLocation, 1, GL_FALSE, value_ptr(this->m_transform));
}

const float TransformComponent::DistanceFrom(const vec3& otherPos) const 
{
	return length(m_position - otherPos);
}

const float TransformComponent::DistanceFrom(const TransformComponent& other) const
{
	return this->DistanceFrom(other.m_position);
}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;

EMSCRIPTEN_BINDINGS(TransformComponent_JS)
{
	class_<BaseComponent>("BaseComponent");

	class_<TransformComponent, base<BaseComponent>>("TransformComponent")
		.constructor()
		.function("GetPosition", &TransformComponent::GetPosition)
		.function("SetPosition", select_overload<TransformComponent& (float, float, float)>(&TransformComponent::SetPosition))
		.function("SetScale", select_overload<TransformComponent& (float, float, float)>(&TransformComponent::SetScale))
		.function("GetScale", &TransformComponent::GetScale);
}

#endif