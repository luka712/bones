#pragma once

#ifndef VERTEX_BUFFER_WINDOW_H

#define VERTEX_BUFFER_WINDOW_H

#include "core_types.h"

namespace Bones
{
	class Engine;

	namespace Buffers
	{
		class VertexBuffer;
	}

	namespace UI
	{

		namespace Windows
		{
			/// <summary>
			/// The Vertex bufer window.
			/// </summary>
			class VertexBufferWindow : public ILifeCycle<VertexBufferWindow>
			{
			public:
				VertexBufferWindow(Bones::Engine& engine);

				void Load_impl();
				void Initialize_impl();
				void Update_impl(F32);
				void Render_impl();
				void Destroy_impl();

				void SetVertexBuffer(Buffers::VertexBuffer* iBuffer);
			private:
				Engine& m_engine;
				Buffers::VertexBuffer* m_vertexBuffer = nullptr;
				char m_nameBuffer[128];

				void ShowNameSection();
				void ShowPropertiesTableSection();
				void ShowVerticesTableSection();
			};
		}
	}
}

#endif // !VERTEX_BUFFER_WINDOW_H
