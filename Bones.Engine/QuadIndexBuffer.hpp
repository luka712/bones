#pragma once

#include "IndexBuffer.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{
		class QuadIndexBuffer final : public IndexBuffer
		{
		public:
			QuadIndexBuffer() : IndexBuffer()
			{
				const U8 m_quadIndexData[6] = {
					0, 2, 1,
					1, 2, 3
				};

				m_name = "Quad Index Buffer";
				m_count = 6;
				m_structComponentLength = Bones::IndicesByteSize::UNSIGNED_BYTE;
				m_glType = GL_UNSIGNED_BYTE;
				Bones::Utils::ArrayPtrToVectorData(m_quadIndexData, 6, m_data);
				m_length = m_data.size();
			}
		};
	}
}
