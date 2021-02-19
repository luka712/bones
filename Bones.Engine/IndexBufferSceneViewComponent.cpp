#include "IndexBufferSceneViewComponent.hpp"
#include "IndexBuffer.hpp"
#include "UIManager.hpp"
#include "SceneViewUIToolComponent.hpp"

using namespace Bones::UI::Tools::SceneView;

IndexBufferSceneViewComponent::IndexBufferSceneViewComponent(IndexBuffer* iBuffer, SceneViewUIToolComponent* sceneViewParent)
	: m_indexBuffer(iBuffer), m_viewParentPtr(sceneViewParent)
{
}

void IndexBufferSceneViewComponent::Initialize()
{
	if (m_state >= Bones::State::Initialized) return;

	m_state = Bones::State::Initialized;

	m_label = UIManager::CreateSelectableLabelComponent(m_viewParentPtr->m_buffersTree, m_indexBuffer->m_name);
	m_label->m_onSelected = [&](Bones::Event<SelectableLabelUIComponent&> cmp) -> void
	{
		//m_onSelected({ *this });
		//// raise event when selected to notify insepctor screen.
		//UIToolsEventManager::RaiseOnSceneViewSceneObjectSelected({ *m_sceneObject });
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

IndexBufferSceneViewComponent::~IndexBufferSceneViewComponent()
{
	m_indexBuffer = nullptr;
	m_viewParentPtr = nullptr;
	m_state = State::Destroyed;
}
