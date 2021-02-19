#pragma once

#include "VertexBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		class QuadNormalBuffer final : public VertexBuffer
		{
		private:
			const float data[12] = {
				0.0, 1.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 1.0, 0.0
			};

		public:
			QuadNormalBuffer() : VertexBuffer("a_normal", 3, data, 12) 
			{
				m_name = "Quad Normal Buffer";
			};
		};
	}
}