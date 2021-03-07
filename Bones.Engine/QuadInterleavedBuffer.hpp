#pragma once

#include "InterleavedBuffer.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// Quad interleaved buffer.
		/// </summary>
		class QuadInterleavedBuffer final : public InterleavedBuffer
		{
		public:
			QuadInterleavedBuffer() : InterleavedBuffer()
			{
				const F32 data[32] = {
					// x  y    z     t     s 
					-0.5, 0.0, -0.5, 1.0f, 1.0f, 0.0, 1.0, 0.0,
					 0.5, 0.0, -0.5, 0.0f, 1.0f, 0.0, 1.0, 0.0,
					-0.5, 0.0,  0.5, 1.0f, 0.0f, 0.0, 1.0, 0.0,
					 0.5, 0.0,  0.5, 0.0f, 0.0f, 0.0, 1.0, 0.0,
				};
				m_name = "Quad Interleaved Buffer";
				m_count = 32;
				m_attributes =
				{
					// layout attrib location, size, offset, layout name ( if attrib location not specified ) 
					  { 0, 3, sizeof(F32), 0, "a_position", },
					  { 1, 2, sizeof(F32), sizeof(F32) * 3, "a_texCoord", },
					  { 2, 3, sizeof(F32), sizeof(F32) * 5, "a_normal", },
				};

				Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
				m_length = m_data.size();
			};
		};
	}
}