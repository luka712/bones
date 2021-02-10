#include "SceneObjectSceneViewComponent.hpp"
#include "UIManager.hpp"
#include "SceneViewUIToolComponent.hpp"
#include "SceneObject.hpp"
#include "UIToolsEventManager.hpp"
#include "WindowUIComponent.hpp"

using namespace Bones::UI::Tools::SceneView;

SceneObjectSceneViewComponent::SceneObjectSceneViewComponent(SceneObject* obj, SceneViewUIToolComponent* sceneViewParent)
{
	m_sceneObject = obj;
	m_viewParentPtr = sceneViewParent;
}

void SceneObjectSceneViewComponent::Initialize()
{
	if (m_state >= Bones::State::Initialized) return;

	m_state = Bones::State::Initialized;

	m_label = UIManager::CreateSelectableLabelComponent(m_viewParentPtr->m_sceneTree, m_sceneObject->m_name);
	m_label->m_onSelected = [&](Bones::Event<SelectableLabelUIComponent&> cmp) -> void
	{
		m_onSelected({ *this });
		// raise event when selected to notify insepctor screen.
		UIToolsEventManager::RaiseOnSceneViewSceneObjectSelected({ *m_sceneObject });
	};

	m_onSceneObjectNameChanged = [&](Bones::Event<SceneObject&> evt) -> void
	{
		if (&evt.m_callee == m_sceneObject)
		{
			m_label->m_name = evt.m_callee.m_name;
		}
	};

	UIToolsEventManager::OnSceneObjectNameChanged(m_onSceneObjectNameChanged);

	m_state = Bones::State::Initialized;
}

void SceneObjectSceneViewComponent::SetSelected(bool val)
{
	m_label->m_selected = val;
}

bool SceneObjectSceneViewComponent::IsSelected()
{
	return m_label->m_selected;
}

SceneObjectSceneViewComponent::~SceneObjectSceneViewComponent()
{
	m_state = Bones::State::Destroyed;
	UIToolsEventManager::RemoveOnSceneObjectNameChanged(m_onSceneObjectNameChanged);
}
