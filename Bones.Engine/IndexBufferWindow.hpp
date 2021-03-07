#pragma once

#ifndef INDEX_BUFFER_WINDOW_H

#define INDEX_BUFFER_WINDOW_H

#include "core_types.h"

namespace Bones
{
	class Engine;

	namespace Buffers
	{
		class IndexBuffer;
	}

	namespace UI
	{

		namespace Windows
		{
			/// <summary>
			/// The index bufer window.
			/// </summary>
			class IndexBufferWindow : public ILifeCycle<IndexBufferWindow>
			{
			public:
				IndexBufferWindow(Bones::Engine& engine);

				void Load_impl();
				void Initialize_impl();
				void Update_impl(F32);
				void Render_impl();
				void Destroy_impl();

				void SetIndexBuffer(Buffers::IndexBuffer* iBuffer);
			private:
				Engine& m_engine;
				Buffers::IndexBuffer* m_indexBuffer = nullptr;

				// Ui specific
				char m_nameBuffer[128];

				void ShowNameSection();
				void ShowPropertiesTableSection();
				void ShowIndicesTableSection();
			};
		}
	}
}

#endif // !INDEX_BUFFER_WINDOW_H
