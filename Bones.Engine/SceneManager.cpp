#include "SceneManager.hpp"
#include "Scene.hpp"
#include "Constants.hpp"

using Bones::Managers::SceneManager;

map<string, Scene*> SceneManager::m_scenes;
Scene* SceneManager::m_currentScene;
vector<function<void(Scene& scene)>> SceneManager::m_onSceneCretedEvents;

Scene* SceneManager::Get(const string& name)
{
	if (m_scenes.find(name) == m_scenes.end())
	{
		LOG_WARN_FORMAT("Cannot get scene. Scene %s does not exist.", name.c_str());
	}
	return m_scenes.at(name);
}

Scene* SceneManager::CreateScene(const string& name)
{
	Scene* scene = new Scene(name);
	if (m_currentScene == nullptr)
	{
		m_currentScene = scene;
	}
	m_scenes.emplace(name, scene);

	// Raise events.
	for (auto& fn : m_onSceneCretedEvents)
	{
		fn(*scene);
	}

	scene->Load();
	scene->Initialize();

	return scene;
}

void SceneManager::OnSceneCreated(function<void(Scene& scene)> cb)
{
	m_onSceneCretedEvents.push_back(cb);
}

void SceneManager::Delete(const string& name)
{
	map<string, Scene*>::iterator it = m_scenes.find(name);
	if (it == m_scenes.end())
	{
		LOG_WARN_FORMAT("Cannot delete scene. Scene %s does not exist.", name.c_str());
	}
	
	if (it->second->m_state != State::Destroyed)
	{
		delete it->second;
	}
	m_scenes.erase(name);
}

void SceneManager::Destroy()
{
	for (map<string, Scene*>::iterator it = m_scenes.begin(); it != m_scenes.end(); ++it)
	{
		if (it->second->m_state != State::Destroyed)
		{
			delete it->second;
		}
	}
	m_scenes.clear();
	m_currentScene = nullptr;
}
