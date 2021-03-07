#pragma once

#include "VertexBuffer.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{
		class QuadVertexBuffer final : public VertexBuffer
		{
		private:
		

		public:
			QuadVertexBuffer() : VertexBuffer()
			{
				const F32 data[12] = {
					-0.5f, 0.0f, -0.5f,
					 0.5f, 0.0f, -0.5f,
					-0.5f, 0.0f,  0.5f,
					 0.5f, 0.0f,  0.5f,
				};
				m_name = "Quad Vertex Bufer";
				m_layoutName = "a_position";
				m_count = 12;
				m_structSize = 3;
				m_structComponentLength = sizeof(F32);
				m_structLength = m_count / m_structSize;

				Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
				m_length = m_data.size();
			};
		};
	}
}