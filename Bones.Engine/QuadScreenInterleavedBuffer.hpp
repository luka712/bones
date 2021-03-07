#pragma once

#ifndef QUAD_SCREEN_INTERLEAVED_BUFFER_H

#define QUAD_SCREEN_INTERLEAVED_BUFFER_H

#include "InterleavedBuffer.hpp"
#include "utils.h"

using Bones::Buffers::InterleavedBuffer;

namespace Bones
{
	namespace Buffers
	{
		namespace QuadScreenBuffers
		{
			class QuadScreenInterleavedBuffer final : public InterleavedBuffer
			{

			public:
				QuadScreenInterleavedBuffer() : InterleavedBuffer()
				{
					const F32 data[24] = {
						// positions	// texCoords
						-1.0f, 1.0f,	0.0f, 1.0f,
						-1.0f, -1.0f,	0.0f, 0.0f,
						 1.0f, -1.0f,	1.0f, 0.0f,

						-1.0f, 1.0f,	0.0f, 1.0f,
						 1.0f, -1.0f,	1.0f, 0.0f,
						 1.0f, 1.0f,    1.0f, 1.0f
					};
					m_name = "Quad Screen Interleaved Buffer";
					m_count = 24;
					m_attributes =
					{
						// attrib location, size, offset, layout name ( if attrib location is not specified ) 
						{ 0, 2, sizeof(F32), 0, "a_position" },
						{ 1, 2, sizeof(F32), sizeof(F32) * 2 , "a_texCoord", }
					};
				
					Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
					m_length = m_data.size();
				};
			};
		}
	}
}

#endif // !QUAD_SCREEN_INTERLEAVED_BUFFER_H
