#pragma once

#include "IndexBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		class QuadIndexBuffer final : public IndexBuffer
		{
		private:
			const GLuint data[6] = {
				0, 2, 1,
				1, 2, 3
			};

		public:
			QuadIndexBuffer() : IndexBuffer(data, 6) {}
		};
	}
}