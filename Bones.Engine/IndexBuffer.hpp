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
		class IndexBuffer : public BaseBuffer
		{
		public:
			// Length of data in array. To not be confused with count. If there is index buffer with 
			// 4 elements of unsigned shorts ( 2 bytes ) length is 8.
			I32 m_length;

			// Default gl type, which is used when passing data to gpu.
			U32 m_glType = GL_UNSIGNED_INT;

			// can be only used if in debug mode. It's clear in non debug mode.
			std::vector<U8> m_data;

			// size of bytes, used when loading to GPU
			Bones::IndicesByteSize m_byteSize;

			IndexBuffer(const U32* data, const I32 count);
			IndexBuffer(const U8* data, const I32 length, const Bones::IndicesByteSize byteSize);

			// -- interace methods
			void Initialize();
			void Initialize(const U32 program);
			void Bind()  override;
			void Unbind()  override;
			inline const std::string Type() const noexcept { return "index_buffer"; }

			void Destroy();

			void GetDataAsU16(std::vector<U16>& ref);

			~IndexBuffer();
		protected:
			const std::string m_initializeEventName = "index_buffer.initialized";
			const std::string m_destroyEventName = "index_buffer.destroyed";
		};

	}
}
