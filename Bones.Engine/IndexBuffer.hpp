#pragma once

#include "BaseBuffer.hpp"
#include "core_types.h"
#include <vector>
#include "sdl_include.h"

using namespace std;

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// The index buffer.
		/// </summary>
		class IndexBuffer : public BaseBuffer<IndexBuffer>
		{
		public:
			// Default gl type, which is used when passing data to gpu.
			U32 m_glType = GL_UNSIGNED_INT;

			// can be only used if in debug mode. It's clear in non debug mode.
			std::vector<U8> m_data;

			// size of bytes, used when loading to GPU
			Bones::IndicesByteSize m_structComponentLength = Bones::IndicesByteSize::NONE;

			IndexBuffer(const U32* data, const I32 count);
			IndexBuffer(const U8* data, const I32 length, const Bones::IndicesByteSize byteSize);

			// -- interace methods
			void Initialize_impl();
			void Initialize_impl(const U32 program);
			void Bind_impl();
			void Unbind_impl();
			void DeleteBuffer_impl();
			void Destroy_impl();

			const char* IndicesTypeAsChar();

			~IndexBuffer();
		protected:
			const std::string m_initializeEventName = "index_buffer.initialized";
			const std::string m_destroyEventName = "index_buffer.destroyed";

			IndexBuffer();
		};

	}
}
