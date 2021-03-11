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
		namespace Windows
		{
			class HierarchyWindow;
			class IndexBufferWindow;
			class VertexBufferWindow;
			class InterleavedBufferWindow;
			class PostProcessFramebufferWindow;
		}

		/// <summary>
		/// The Dat GUI UI manager.
		/// </summary>
		class UIManager final : public ILifeCycle<UIManager>, 
			public BaseOnSDLEvent<UIManager>, 
			public BaseOnBeforeRender<UIManager>,
			public BaseOnAfterRender<UIManager>
		{
		public:
			UIManager(Bones::Engine& engine);
			~UIManager();

			void Load_impl();
			void Initialize_impl();
			void Update_impl(F32 dt);
			void Render_impl();
			void Destroy_impl();

			// -- events
			void OnSDLEvent_impl(const SDL_Event& evt);
			void OnBeforeRender_impl();
			void OnAfterRender_impl();

		private:
			Bones::Engine& m_engine;
			Bones::UI::Windows::HierarchyWindow* m_hierarchyWindow;
			Bones::UI::Windows::IndexBufferWindow* m_indexBufferWindow;
			Bones::UI::Windows::VertexBufferWindow* m_vertexBufferWindow;
			Bones::UI::Windows::InterleavedBufferWindow* m_interleavedBufferWindow;
			Bones::UI::Windows::PostProcessFramebufferWindow* m_postProcessFramebufferWindow;
		};
	}
}

#endif // !UIMANAGER_H

