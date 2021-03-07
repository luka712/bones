#pragma once

#include "IndexBuffer.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// The cube index buffer.
		/// </summary>
		class CubeIndexBuffer final : public IndexBuffer
		{
		public:
			CubeIndexBuffer() : IndexBuffer()
			{
				const U8 data[36] = {
				   0,  1,  2,      0,  2,  3,    // front
				   4,  5,  6,      4,  6,  7,    // back
				   8,  9,  10,     8,  10, 11,   // top
				   12, 13, 14,     12, 14, 15,   // bottom
				   16, 17, 18,     16, 18, 19,   // right
				   20, 21, 22,     20, 22, 23,   // left
				};

				m_count = 36;
				m_structComponentLength = Bones::IndicesByteSize::UNSIGNED_BYTE;
				m_name = "Cube Index Buffer";
				Bones::Utils::ArrayPtrToVectorData(data, 6, m_data);
				m_length = m_data.size();
			};
		};
	}
}