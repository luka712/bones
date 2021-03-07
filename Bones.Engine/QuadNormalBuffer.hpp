#pragma once

#include "VertexBuffer.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{
		class QuadNormalBuffer final : public VertexBuffer
		{
		private:
			

		public:
			QuadNormalBuffer() : VertexBuffer() 
			{
				const F32 data[12] = {
				   0.0, 1.0, 0.0,
				   0.0, 1.0, 0.0,
				   0.0, 1.0, 0.0,
				   0.0, 1.0, 0.0
				};
				m_name = "Quad Normal Buffer";
				m_layoutName = "a_normal";
				m_count = 12;
				m_structSize = 3;
				m_structComponentLength = sizeof(F32);
				m_countOfStructs = m_count / m_structSize;
				m_structLength = m_structComponentLength * m_structSize;

				Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
				m_length = m_data.size();
			};
		};
	}
}