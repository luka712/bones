#pragma once

#ifndef UIMANAGER_H

#define UIMANAGER_H

#include "core_types.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "IEngineEvents.hpp"


namespace Bones
{
	class Engine;
	struct IEvent;

	namespace UI
	{
		/// <summary>
		/// The Dat GUI UI manager.
		/// </summary>
		class UIManager final : public ILifeCycle<UIManager>, public BaseOnSDLEvent<UIManager>
		{
		public:
			UIManager(Bones::Engine& engine);
			~UIManager();

			void Load_impl();
			void Initialize_impl();
			void Update_impl(F32 dt);
			void Render_impl();
			void Destroy_impl();

			void OnSDLEvent_impl(const SDL_Event& evt);
		private:
			Bones::Engine& m_engine;
		};
	}
}

#endif // !UIMANAGER_H

