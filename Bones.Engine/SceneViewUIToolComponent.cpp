#include "SceneViewUIToolComponent.hpp"
#include "UIManager.hpp"
#include "BaseUIComponent.hpp"
#include "WindowUIComponent.hpp"
#include "TreeUIComponent.hpp"
#include "Scene.hpp"
#include "SceneManager.hpp"
#include "BuffersManager.hpp"
#include "SceneObjectSceneViewComponent.hpp"
#include "IndexBufferSceneViewComponent.hpp"
#include "BaseSceneViewEntryComponent.hpp"
#include "IndexBuffer.hpp"
#include "Constants.hpp"

using namespace Bones::UI::Core;
using namespace Bones::UI::Tools;
using namespace Bones::UI::Tools::SceneView;
using namespace Bones::Managers;

void SceneViewUIToolComponent::HandleScene()
{
	// On scene created
	SceneManager::OnSceneCreated([&](Scene& scene) -> void
	{
		// If there is old scene tree. Destroy it.
		if (m_sceneTree)
		{
			UIManager::DestroyComponent(m_sceneTree);
		}

		m_sceneTree = UIManager::CreateTreeComponent(m_window, SceneManager::m_currentScene->m_name);
		m_window->AddComponent(m_sceneTree);

		// Register events 
		scene.OnSceneObjectAdded([&](SceneObject& obj) -> void
		{
			auto cmp = new SceneObjectSceneViewComponent(&obj, this);
			cmp->Initialize();
			cmp->m_onSelected = [&](Bones::Event< SceneObjectSceneViewComponent&> evt) -> void
			{
				for (BaseSceneViewEntryComponent* entry : m_viewEntryComponents)
				{
					if (entry != &evt.m_callee)
					{
						entry->SetSelected(false);
					}
				}
			};
			m_viewEntryComponents.push_back(cmp);
		});
	});
}

void SceneViewUIToolComponent::HandleBuffers()
{
	// If there is old scene tree. Destroy it.
	if (m_buffersTree)
	{
		UIManager::DestroyComponent(m_buffersTree);
	}

	m_buffersTree = UIManager::CreateTreeComponent(m_window, "Buffer Attributes");
	m_window->AddComponent(m_buffersTree);
	BuffersManager::OnIndexBufferCreated([&](const Bones::Event<IndexBuffer*>& evt) -> void
	{
		// Index buffer scene view component.
		auto cmp = new IndexBufferSceneViewComponent(evt.m_callee, this);
		cmp->Initialize();

		// events.

		m_viewEntryComponents.push_back(cmp);
	});

	//for (std::unique_ptr<IndexBuffer>& uPtr : BuffersManager::m_indexBufferCache)
	//{
		// Index buffer scene view component.
		//auto cmp = new IndexBufferSceneViewComponent(&*uPtr, this);
		//cmp->Initialize();
		
	//}
}

void SceneViewUIToolComponent::Initialize()
{
	if (m_state == State::New)
	{
		m_window = UIManager::CreateWindowComponent("Scene", { 0,0, DEFAULT_WIDTH / 6, DEFAULT_HEIGHT });

		HandleScene();
		HandleBuffers();
	}
	m_state = State::Initialized;
}

void SceneViewUIToolComponent::DestroyComponent(BaseToolUIComponent* cmp)
{
	for (size_t i = 0; i < m_viewEntryComponents.size(); i++)
	{
		if (m_viewEntryComponents.at(i) == cmp)
		{
			delete m_viewEntryComponents.at(i);
			m_viewEntryComponents.erase(m_viewEntryComponents.begin() + i);
			break;
		}
	}
}

void SceneViewUIToolComponent::Destroy()
{
	DELETE_VECTOR(m_viewEntryComponents);
}

SceneViewUIToolComponent::~SceneViewUIToolComponent()
{
	Destroy();
}
