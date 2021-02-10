#pragma once

#include "OpenGL_ES_3_0_Renderer.hpp"
#include "OpenGL_4_6_Renderer.hpp"
#include "Constants.hpp"

using namespace Bones::Renderer;

namespace Bones
{
	typedef void(*InitializeCallback)();
	typedef void(*LoadCallback)();

	// values from SDL_GetTicks()
	struct TimeData
	{
		// since start of program.
		Uint32 m_elapsedTime = 0;

		// Elapsed time since start of frame, until the end of frame.
		Uint32 m_deltaTime = 0;
	};

	/// <summary>
	/// The engine.
	/// </summary>
	class Engine final 
	{
	private:
		BaseRenderer* m_renderer = nullptr;
		bool m_running;
		TimeData m_timeData;

#if EMSCRIPTEN_RUNTIME == false
		// used for SDL GetTicks(). Used only in desktop mode.
		int m_FPS = 60;
#endif 

		void BeforeUpdate()  ;
		void Update();
		void AfterUpdate()  ;
		void Draw()  const;
	public:
		State m_state = State::New;
		std::function<void(SDL_Window*)> m_initializedEvent = [](SDL_Window* win) ->void {};
		std::function<void(SDL_Event&)> m_pollEvents = [](SDL_Event& event) -> void {};
		std::function<void(Uint32 dt)> m_updateEvent = [](Uint32 dt) -> void{};
		std::function<void()> m_drawEvent = []() -> void {};
		std::function<void()> m_destroyEvent = []() -> void {};

		Engine();
		~Engine();

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
		void Initialize(InitializeCallback = nullptr);
		void Load(LoadCallback = nullptr);
		void Run();
		void Destroy();
#pragma endregion
	};
}
