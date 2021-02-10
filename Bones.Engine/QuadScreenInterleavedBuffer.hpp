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
				const float data[24] = {
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
					{ 0, "a_position", 2, 0 },
					{ 1, "a_texCoord", 2, 2 }
				}
				) {};
			};
		}
	}
}

#endif // !QUAD_SCREEN_INTERLEAVED_BUFFER_H
