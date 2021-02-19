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
			const F32 data[32] = {
				// x  y    z     t     s 
				-0.5, 0.0, -0.5, 1.0f, 1.0f, 0.0, 1.0, 0.0,
				 0.5, 0.0, -0.5, 0.0f, 1.0f, 0.0, 1.0, 0.0,
				-0.5, 0.0,  0.5, 1.0f, 0.0f, 0.0, 1.0, 0.0,
				 0.5, 0.0,  0.5, 0.0f, 0.0f, 0.0, 1.0, 0.0,
			};

		public:
			QuadInterleavedBuffer() : InterleavedBuffer( data, 32, vector<BufferAttribute> 
				{
				  // layout attrib location, size, offset, layout name ( if attrib location not specified ) 
					{ 0, 3, 0, "a_position", },
					{ 1, 2, 3, "a_texCoord", },
					{ 2, 3, 5, "a_normal", },
				}
			)
			{
				m_name = "Quad Interleaved Buffer";
			};
		};
	}
}