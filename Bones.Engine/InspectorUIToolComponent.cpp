#include "InspectorUIToolComponent.hpp"
#include "UIManager.hpp"
#include "SceneManager.hpp"
#include "UIToolsEventManager.hpp"
#include "SceneObjectInspectorComponent.hpp"
#include "WindowUIComponent.hpp"

using namespace Bones::UI::Core;
using namespace Bones::UI::Tools;
using namespace Bones::Managers;


void InspectorUIToolComponent::Initialize()
{
	if (m_state == State::New)
	{
		m_window = UIManager::CreateWindowComponent("Component", { DEFAULT_WIDTH - (DEFAULT_WIDTH / 6), 0, (DEFAULT_WIDTH / 6), DEFAULT_HEIGHT });

		UIToolsEventManager::OnSceneViewSceneObjectSelected([&](Bones::Event<SceneObject&> evt) -> void
		{
			if (m_inspectorSceneObjectComponent != nullptr)
			{
				delete m_inspectorSceneObjectComponent;
			}

			m_inspectorSceneObjectComponent = new SceneObjectInspectorComponent(m_window, &evt.m_callee);
			m_inspectorSceneObjectComponent->Initialize();
		});

	}
}
