#include "UIToolsEventManager.hpp"

using namespace Bones::UI::Tools;

std::vector < std::function<void(Bones::Event<SceneObject&>)>> UIToolsEventManager::m_sceneViewSceneObjectSelectedEvents;
std::vector < std::function<void(Bones::Event<SceneObject&>)>> UIToolsEventManager::m_sceneObjectNameChangedEvents;
Bones::State UIToolsEventManager::m_state = Bones::State::New;

void UIToolsEventManager::Initialize()
{
	m_state = Bones::State::Initialized;
}

void UIToolsEventManager::Destroy()
{
	m_sceneViewSceneObjectSelectedEvents.clear();
}

void UIToolsEventManager::OnSceneViewSceneObjectSelected(std::function<void(Bones::Event<SceneObject&>)> cb)
{
	m_sceneViewSceneObjectSelectedEvents.push_back(cb);
}

void UIToolsEventManager::RaiseOnSceneViewSceneObjectSelected(const Bones::Event<SceneObject&>& evt)
{
	for (auto& cb : m_sceneViewSceneObjectSelectedEvents)
	{
		cb(evt);
	}
}

void UIToolsEventManager::OnSceneObjectNameChanged(std::function<void(Bones::Event<SceneObject&>)> cb)
{
	m_sceneObjectNameChangedEvents.push_back(cb);
}

void UIToolsEventManager::RaiseOnSceneObjectNameChanged(const Bones::Event<SceneObject&>& evt)
{
	for (auto& cb : m_sceneObjectNameChangedEvents)
	{
		cb(evt);
	}
}

void UIToolsEventManager::RemoveOnSceneObjectNameChanged(std::function<void(Bones::Event<SceneObject&>)> cb)
{
	for (size_t i = 0; i < m_sceneObjectNameChangedEvents.size(); i++)
	{
		auto _cb = m_sceneObjectNameChangedEvents[i];
		if (&_cb == &cb)
		{
			m_sceneObjectNameChangedEvents.erase(m_sceneObjectNameChangedEvents.begin() + i);
			break;
		}
	}
}



