#pragma once

#include "VertexBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		class QuadVertexBuffer final : public VertexBuffer
		{
		private:
			const F32 data[12] = {
				-0.5, 0.0, -0.5,
				 0.5, 0.0, -0.5,
				-0.5, 0.0,  0.5,
				 0.5, 0.0,  0.5,
			};

		public:
			QuadVertexBuffer() : VertexBuffer("a_position", 3, data, 12)
			{
				m_name = "Quad Vertex Bufer";
			};
		};
	}
}