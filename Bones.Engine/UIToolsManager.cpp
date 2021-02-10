#include "UIToolsManager.hpp"
#include "BaseToolUIComponent.hpp"
#include "InspectorUIToolComponent.hpp"
#include "SceneViewUIToolComponent.hpp"
#include "UIManager.hpp"

using namespace Bones::UI::Core;
using namespace Bones::UI::Tools;

State UIToolsManager::m_state = State::New;
vector<BaseToolUIComponent*> UIToolsManager::m_components;


void UIToolsManager::Initialize()
{
	if (m_state == State::New)
	{
		auto sceneMenu = new SceneViewUIToolComponent();
		auto inspectorMenu = new InspectorUIToolComponent();
		sceneMenu->Initialize();
		inspectorMenu->Initialize();

		m_components.push_back(sceneMenu);
		m_components.push_back(inspectorMenu);
	}
	m_state = State::Initialized;
}

void UIToolsManager::Destroy()
{
	for (size_t i = 0; i < m_components.size(); i++)
	{
		delete m_components.at(i);
	}
	m_components.clear();
	m_state = State::Destroyed;
}