#pragma once

#ifndef POST_PROCESS_FRAMEBUFFER_WINDOW_H

#define POST_PROCESS_FRAMEBUFFER_WINDOW_H

#include "core_types.h"

namespace Bones
{
	class Engine;

	namespace Framebuffers
	{
		namespace PostProcess
		{
			class PostProcessFramebuffer;
		}
	}

	namespace UI
	{

		namespace Windows
		{
			/// <summary>
			/// The Vertex bufer window.
			/// </summary>
			class PostProcessFramebufferWindow : public ILifeCycle<PostProcessFramebufferWindow>
			{
			public:
				PostProcessFramebufferWindow(Bones::Engine& engine);

				void Load_impl();
				void Initialize_impl();
				void Update_impl(F32);
				void Render_impl();
				void Destroy_impl();

				void SetPostProcessFramebuffer(Framebuffers::PostProcess::PostProcessFramebuffer* framebuffer);
			private:
				Engine& m_engine;
				Framebuffers::PostProcess::PostProcessFramebuffer* m_postProcessFramebuffer = nullptr;
				char m_nameBuffer[128];

				void ShowNameSection();
				void ShowPropertiesTableSection();
			};
		}
	}
}

#endif // !POST_PROCESS_FRAMEBUFFER_WINDOW_H
