#pragma once

#ifndef QUAD_SCREEN_INTERLEAVED_BUFFER_H

#define QUAD_SCREEN_INTERLEAVED_BUFFER_H

#include "InterleavedBuffer.hpp"

using Bones::Buffers::InterleavedBuffer;

namespace Bones
{
	namespace Buffers
	{
		namespace QuadScreenBuffers
		{
			class QuadScreenInterleavedBuffer final : public InterleavedBuffer
			{

			private:
				const F32 data[24] = {
					// positions	// texCoords
					-1.0f, 1.0f,	0.0f, 1.0f,
					-1.0f, -1.0f,	0.0f, 0.0f,
					 1.0f, -1.0f,	1.0f, 0.0f,

					-1.0f, 1.0f,	0.0f, 1.0f,
					 1.0f, -1.0f,	1.0f, 0.0f,
					 1.0f, 1.0f,    1.0f, 1.0f
				};

			public:
				QuadScreenInterleavedBuffer() : InterleavedBuffer(data, 24, vector<BufferAttribute>
				{
					// attrib location, size, offset, layout name ( if attrib location is not specified ) 
					{ 0, 2, 0, "a_position" },
					{ 1, 2, 2, "a_texCoord", }
				}
				) 
				{
					m_name = "Quad Screen Interleaved Buffer";
				};
			};
		}
	}
}

#endif // !QUAD_SCREEN_INTERLEAVED_BUFFER_H
