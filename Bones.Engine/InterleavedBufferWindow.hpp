#pragma once

#ifndef INTERLEAVED_BUFFER_WINDOW_H

#define INTERLEAVED_BUFFER_WINDOW_H

#include "core_types.h"

namespace Bones
{
	class Engine;

	namespace Buffers
	{
		class InterleavedBuffer;
	}

	namespace UI
	{

		namespace Windows
		{
			/// <summary>
			/// The Interleaved bufer window.
			/// </summary>
			class InterleavedBufferWindow : public ILifeCycle<InterleavedBufferWindow>
			{
			public:
				InterleavedBufferWindow(Bones::Engine& engine);

				void Load_impl();
				void Initialize_impl();
				void Update_impl(F32);
				void Render_impl();
				void Destroy_impl();

				void SetInterleavedBuffer(Buffers::InterleavedBuffer* iBuffer);
			private:
				Engine& m_engine;
				Buffers::InterleavedBuffer* m_interleavedBuffer = nullptr;
				char m_nameBuffer[128];

				void ShowNameSection();
				void ShowPropertiesTableSection();
				void ShowAttributesTableSection();
				void ShowVerticesTableSection();
			};
		}
	}
}

#endif // !INTERLEAVED_BUFFER_WINDOW_H
