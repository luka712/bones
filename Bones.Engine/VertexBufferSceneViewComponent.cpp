#include "VertexBufferSceneViewComponent.hpp"
#include "VertexBuffer.hpp"
#include "UIManager.hpp"
#include "SceneViewUIToolComponent.hpp"

using namespace Bones::UI::Tools::SceneView;

VertexBufferSceneViewComponent::VertexBufferSceneViewComponent(VertexBuffer* vBuffer, SceneViewUIToolComponent* sceneViewParent)
	: m_vertexBuffer(vBuffer), m_viewParentPtr(sceneViewParent)
{
}

void VertexBufferSceneViewComponent::Initialize()
{
	if (m_state >= Bones::State::Initialized) return;

	m_state = Bones::State::Initialized;

	m_label = UIManager::CreateSelectableLabelComponent(m_viewParentPtr->m_buffersTree, m_vertexBuffer->m_name);
	m_label->m_onSelected = [&](Bones::Event<SelectableLabelUIComponent&> cmp) -> void
	{
	//	//m_onSelected({ *this });
	//	//// raise event when selected to notify insepctor screen.
	//	//UIToolsEventManager::RaiseOnSceneViewSceneObjectSelected({ *m_sceneObject });
	};

	/*m_onSceneObjectNameChanged = [&](Bones::Event<SceneObject&> evt) -> void
	{
		if (&evt.m_callee == m_sceneObject)
		{
			m_label->m_name = evt.m_callee.m_name;
		}
	};*/

	// UIToolsEventManager::OnSceneObjectNameChanged(m_onSceneObjectNameChanged);

	m_state = Bones::State::Initialized;
}

VertexBufferSceneViewComponent::~VertexBufferSceneViewComponent()
{
	m_vertexBuffer = nullptr;
	m_viewParentPtr = nullptr;
	m_state = State::Destroyed;
}
