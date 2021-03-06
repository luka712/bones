#include "Engine.hpp"
#include "GeometryManager.hpp"
#include "ShaderManager.hpp"
#include "TextureManager.hpp"
#include "FramebufferManager.hpp"
#include "BuffersManager.hpp"
#include "MaterialManager.hpp"
#include "MeshManager.hpp"
#include "SceneManager.hpp"
#include "EventQueue.hpp"
#include "UIManager.hpp"

using namespace Bones;

using namespace Bones::Managers;

Engine::Engine()
{
	m_running = true;

#if TARGET_OPENGL_4_6
	m_renderer = new OpenGL_4_6_Renderer();
#else 
	m_renderer = new OpenGL_ES_3_0_Renderer();
#endif 
}

Engine::~Engine()
{
	m_state = State::Destroyed;
	Destroy();
}

Engine& Bones::Engine::UseUserInterface()
{
	if (m_uiManager == nullptr)
	{
		m_uiManager = new Bones::UI::UIManager(*this);
	}
	return *this;
}


void Engine::Load(LoadCallback)
{
	m_uiManager->Load();
	if (SceneManager::m_currentScene)
		SceneManager::m_currentScene->Load();

	m_state = State::Loaded;
}


void Engine::Initialize()
{	
	m_renderer->Initialize();
	m_uiManager->Initialize();
	if (SceneManager::m_currentScene)
		SceneManager::m_currentScene->Initialize();


	m_onInitializedEvent.Invoke(IEvent("engine.initialized", Bones::EventCategory::EngineEvent,
		{
			{ "window", Bones::Variant(m_renderer->m_window) },
			{ "rendering_context", Bones::Variant(m_renderer->m_glContext) }
		}));
}

void Engine::Run()
{
#if EMSCRIPTEN_RUNTIME == false
	while (m_running)
	{
#endif 
		m_timeData.m_elapsedTime = SDL_GetTicks();

		// Core calls only if scene exists
		if (SceneManager::m_currentScene)
		{
			BeforeUpdate();
			Update();
			AfterUpdate();

			BeforeRender();
			Render();
			AfterRender();
			m_renderer->SwapWindow();
		}

		// End core calls

		m_timeData.m_deltaTime = SDL_GetTicks() - m_timeData.m_elapsedTime;
		U32 frameInMs = 1000U / m_FPS;
#if EMSCRIPTEN_RUNTIME == false // delay does not work in wasm ctx
		if (frameInMs > m_timeData.m_deltaTime)
		{
			SDL_Delay(frameInMs - (m_timeData.m_deltaTime));
		}
	}
#endif
}

void Engine::Destroy()
{
	m_running = false;

	delete m_renderer;
	m_renderer = nullptr;

	m_uiManager->Destroy();

	BuffersManager::Destroy();
	FramebufferManager::Delete();
	ShaderManager::Delete();
	TextureManager::Delete();
	GeometryManager::Delete();
	MaterialManager::Delete();
	MeshManager::Destroy();
	SceneManager::Destroy();

	m_destroyEvent();
}

void Bones::Engine::AddSDLEventListener(Bones::IOnSDLEvent* listener)
{
	m_onSDLEvents.emplace_back(listener);
}

void Engine::BeforeUpdate()
{
	auto controlComp = SceneManager::m_currentScene->GetActiveCamera().GetControlComponent();
	if (controlComp != nullptr)
	{
		controlComp->BeforeUpdate();
	}
}

void Engine::Update()
{
	Bones::Events::EventQueue::Update();

	Scene& scene = *SceneManager::m_currentScene;
	SDL_Event event;
	while (SDL_PollEvent(&event)) {

		m_uiManager->OnSDLEvent(event);

		// notify outside clients with poll events.
		for (auto& entry : m_onSDLEvents)
			entry->OnSDLEvent(event);

		m_pollEvents(event);

		// engine components
		switch (event.type) {
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				m_running = false;
			}
		case SDL_KEYUP:
		case SDL_MOUSEMOTION:
		case SDL_MOUSEWHEEL:
		case SDL_MOUSEBUTTONDOWN:
		case SDL_MOUSEBUTTONUP:
			auto controlComp = scene.GetActiveCamera().GetControlComponent();
			if (controlComp != nullptr)
			{
				controlComp->CaptureEvent(event);
			}
		}
	};

	m_uiManager->Update(m_timeData.m_deltaTime);

	auto& camera = SceneManager::m_currentScene->GetActiveCamera();
	camera.Update();

	// TODO: test point light, move to scriptable
	if (SceneManager::m_currentScene->GetSpotLights().size() > 0)
	{
		auto& spotLight = scene.GetSpotLights()[0];
		auto position = camera.GetTransformComponent().GetPosition();
		position.y -= 0.3f;
		spotLight->MoveAndPoint(position, camera.GetDirection());
	}

	auto& objects = scene.GetObjects();
	for (auto& sceneObject : objects)
	{
		if (sceneObject->m_active)
		{
			sceneObject->GetTransform().Update();
		}
	}

	m_updateEvent(m_timeData.m_deltaTime);
}

void Engine::AfterUpdate()
{
	auto controlComp = SceneManager::m_currentScene->GetActiveCamera().GetControlComponent();
	if (controlComp != nullptr)
	{
		controlComp->BeforeUpdate();
	}
}

void Bones::Engine::BeforeRender()
{
	m_uiManager->OnBeforeRender();
}

void Engine::Render() const
{
	m_renderer->Render(*SceneManager::m_currentScene);
	m_drawEvent();
}

void Engine::AfterRender()
{
	m_uiManager->OnAfterRender();
}


#if EMSCRIPTEN_RUNTIME

using namespace emscripten;

EMSCRIPTEN_BINDINGS(Engine)
{
	class_<Engine>("Engine")
		.constructor()
		.function("GetRenderer", &Engine::GetRenderer, allow_raw_pointers());
}

#endif 