#pragma once

#include "OpenGL_ES_3_0_Renderer.hpp"
#include "OpenGL_4_6_Renderer.hpp"
#include "core_types.h"
#include "EventHandler.hpp"
#include "IEngineEvents.hpp"

using namespace Bones::Renderer;

namespace Bones
{
	namespace UI
	{
		class UIManager;
		class BuffersManager;
	}
}

namespace Bones
{
	typedef void(*LoadCallback)();

	// values from SDL_GetTicks()
	struct TimeData
	{
		// since start of program.
		U32 m_elapsedTime = 0;

		// Elapsed time since start of frame, until the end of frame.
		U32 m_deltaTime = 0;
	};

	/// <summary>
	/// The engine.
	/// </summary>
	class Engine final
	{
	private:
		// the user interface component.
		Bones::UI::UIManager* m_uiManager = nullptr;


		std::vector<Bones::IOnSDLEvent*> m_onSDLEvents;

		// used for SDL GetTicks(). Used only in desktop mode.
		U32 m_FPS = 60;
		bool m_running;
		TimeData m_timeData;
	
		void BeforeUpdate();
		void Update();
		void AfterUpdate();
		void BeforeRender();
		void Render()  const;
		void AfterRender();
	public:
		

		BaseRenderer* m_renderer = nullptr;
		State m_state = State::New;
		
		Bones::EventHandler<> m_onInitializedEvent;
		std::function<void(SDL_Event&)> m_pollEvents = [](SDL_Event& event) -> void {};
		std::function<void(Uint32 dt)> m_updateEvent = [](Uint32 dt) -> void {};
		std::function<void()> m_drawEvent = []() -> void {};
		std::function<void()> m_destroyEvent = []() -> void {};

		Engine();
		~Engine();

		Engine& UseUserInterface();

#pragma region Getters 
		BaseRenderer* GetRenderer() { return m_renderer; }
#pragma endregion

#pragma region Setters 
		/// <summary>
		/// Sets the current scene.
		/// </summary>
		/// <param name="scene">The scene.</param>
		void UseScene(Scene* scene);
#pragma endregion

#pragma region Framework Methods
		void Initialize();
		void Load(LoadCallback = nullptr);
		void Run();
		void Destroy();
#pragma endregion

		void AddSDLEventListener(Bones::IOnSDLEvent* listener);
	};
}
