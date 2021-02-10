#pragma once

#include "InterleavedBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// Quad interleaved buffer.
		/// </summary>
		class QuadInterleavedBuffer final : public InterleavedBuffer
		{
		private:
			const GLfloat data[32] = {
				// x  y    z     t     s 
				-0.5, 0.0, -0.5, 1.0f, 1.0f, 0.0, 1.0, 0.0,
				 0.5, 0.0, -0.5, 0.0f, 1.0f, 0.0, 1.0, 0.0,
				-0.5, 0.0,  0.5, 1.0f, 0.0f, 0.0, 1.0, 0.0,
				 0.5, 0.0,  0.5, 0.0f, 0.0f, 0.0, 1.0, 0.0,
			};

		public:
			QuadInterleavedBuffer() : InterleavedBuffer( data, 32, vector<BufferAttribute> 
				{
					{ 0, "a_position", 3, 0 },
					{ 1, "a_texCoord", 2, 3 },
					{ 2, "a_normal", 3, 5 },
				}
			) {};
		};
	}
}