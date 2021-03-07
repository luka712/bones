#pragma once

#ifndef HIERARCHY_WINDOW_H

#define HIERARCHY_WINDOW_H

#include "core_types.h"
#include "EventHandler.hpp"

namespace Bones
{
	class Engine;

	namespace UI
	{
		namespace Windows
		{
			/// <summary>
			/// The hierarchy window.
			/// </summary>
			class HierarchyWindow : public ILifeCycle<HierarchyWindow>
			{
			public:
				EventHandler<> m_onIndexBufferSelected;
				EventHandler<> m_onVertexBufferSelected;
				EventHandler<> m_onInterleavedBufferSelected;

				HierarchyWindow(Bones::Engine& engine);

				void Load_impl();
				void Initialize_impl();
				void Update_impl(F32);
				void Render_impl();
				void Destroy_impl();
			private:
				Engine& m_engine;
				struct {
					bool m_index;
					bool m_vertices;
					bool m_interleaved;
				} m_showBuffers;
			};
		}
	}
}

#endif // !HIERARCHY_WINDOW_H
