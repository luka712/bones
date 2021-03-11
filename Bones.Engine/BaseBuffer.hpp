#pragma once

#ifndef BASE_BUFFER_H

#define BASE_BUFFER_H

#include "core_types.h"
#include "EventHandler.hpp"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// Base abstract representation of buffer, from which all others inherit from.
		/// IndexBuffer, InterleavedBuffer and VertexBuffer inherit from BaseBuffer.
		/// </summary>
		template<typename T>
		class BaseBuffer : public ILifeCycle<T>
		{
		public:
			/// <summary>
			/// Event handler that fired on initialization.
			/// </summary>
			EventHandler<> m_onInitializedEventHandler;

			/// <summary>
			/// Event handler which is fired when instance is destroyed.
			/// </summary>
			EventHandler<> m_onDestroyEventHandler;

			// count of elements in array. To not be confused with length.
			// For example length might be 8 for indices of unsigned shorts ( 2 bytes per elemt ). Therefore count is 4.
			U32 m_count = 0;

			// total length of buffer. To not be confused with count.
			// For example count might be 4 for indices of unsigned shorts. But length will be 8 since count * sizeof(unsigned short) is 8.
			U64 m_length = 0;

			/// <summary>
			/// The initialize method.
			/// </summary>
			void Initialize()
			{
				static_cast<T*>(this)->Initialize_impl();
			}

			/// <summary>
			/// The initialize method, which creates buffer instance loads data to memory for specific program.
			/// </summary>
			void Initialize(const U32 program)
			{
				static_cast<T*>(this)->Initialize_impl(program);
			}

			/// <summary>
			/// Binds the buffer to be used by GPU.
			/// </summary>
			void Bind()
			{
				static_cast<T*>(this)->Bind_impl();
			}

			/// <summary>
			/// Unbinds the buffer.
			/// </summary>
			void Unbind()
			{
				static_cast<T*>(this)->Unbind_impl();
			}

			/// <summary>
			/// Deletes the buffer from GPU memory.
			/// </summary>
			void DeleteBuffer()
			{
				static_cast<T*>(this)->DeleteBuffer_impl();
			}

		protected:
			// The address of buffer in GPU.
			U32 m_buffer = 0;
		};
	}
}

#endif // !BASE_BUFFER_H