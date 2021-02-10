#pragma once

#include "BaseBuffer.hpp"
#include "Constants.hpp"
#include <vector>

using namespace std;

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// The index buffer.
		/// </summary>
		class IndexBuffer : public BaseBuffer
		{
		public:
			// used to increment id on creation of new instance.
			static unsigned int m_idGen;

			// identifier
			unsigned int m_id;

			// Length of data in array. To not be confused with count. If there is index buffer with 
			// 4 elements of unsigned shorts ( 2 bytes ) length is 8.
			int m_length;

			// can be only used if in debug mode. It's clear in non debug mode.
			std::vector<unsigned char> m_data;

			// size of bytes, used when loading to GPU
			Bones::IndicesByteSize m_byteSize;

			// Default gl type, which is used when passing data to gpu.
			int m_glType = GL_UNSIGNED_INT;

			IndexBuffer(const unsigned int* data, const int count);
			IndexBuffer(const unsigned char* data, const int length, const Bones::IndicesByteSize byteSize);

			void Initialize();
			void Initialize(const unsigned int program);
			void Bind()  override;
			void Unbind()  override;

			void Destroy();
		};


	}
}
