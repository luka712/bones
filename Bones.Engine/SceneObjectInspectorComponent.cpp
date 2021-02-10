#include "SceneObjectInspectorComponent.hpp"
#include "UIManager.hpp"
#include "SceneObject.hpp"
#include "CheckboxUIComponent.hpp"
#include "TextUIComponent.hpp"
#include "UIToolsEventManager.hpp"

using namespace Bones::UI::Tools;

SceneObjectInspectorComponent::SceneObjectInspectorComponent(WindowUIComponent* parentWindow, SceneObject* sceneObject)
	:BaseToolUIComponent()

{
	m_parentWindow = parentWindow;
	m_sceneObjectRef = sceneObject;
}

SceneObjectInspectorComponent::~SceneObjectInspectorComponent()
{
	Destroy();
}

void SceneObjectInspectorComponent::Initialize()
{
	// name
	m_nameText = UIManager::CreateTextComponent(m_parentWindow, m_sceneObjectRef->m_name);
	m_nameText->m_onChanged = [&](Bones::ChangeEvent<TextUIComponent&, string> evt) -> void
	{
		m_sceneObjectRef->m_name = evt.m_value;
		UIToolsEventManager::RaiseOnSceneObjectNameChanged({ *m_sceneObjectRef });
	};

	// active
	m_activeCheckbox = UIManager::CreateCheckboxComponent(m_parentWindow, " - active", m_sceneObjectRef->m_active);
	m_activeCheckbox->m_onChange = [&](Bones::ChangeEvent<CheckboxUIComponent&, bool> evt) -> void
	{
		m_sceneObjectRef->m_active = evt.m_value;
	};
	m_state = State::Initialized;
}

void SceneObjectInspectorComponent::Destroy()
{
	UIManager::DestroyComponent(m_activeCheckbox);
	UIManager::DestroyComponent(m_nameText);
	m_state = State::Destroyed;
}
