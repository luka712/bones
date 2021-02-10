#pragma once

#ifndef BASE_BUFFER_H

#define BASE_BUFFER_H

#include "Constants.hpp"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// Base abstract representation of buffer, from which all others inherit from.
		/// IndexBuffer, InterleavedBuffer and VertexBuffer inherit from BaseBuffer.
		/// </summary>
		class BaseBuffer
		{
		protected:
			// The address of buffer in GPU.
			unsigned int m_buffer = 0;

			// Is buffer already initialized ? 
			bool m_initialized = false;
		
		public:
			// The state of buffer.
			Bones::State m_state = Bones::State::New;

			/// <summary>
			/// Constructor.
			/// </summary>
			BaseBuffer();

			// count of elements in array. To not be confused with length.
			// For example length might be 8 for indices of unsigned shorts ( 2 bytes per elemt ). Therefore count is 4.
			int m_count = 0;

			/// <summary>
			/// The initialize method, which creates buffer instance loads data to memory 
			/// </summary>
			virtual void Initialize() = 0;

			/// <summary>
			/// The initialize method, which creates buffer instance loads data to memory for specific program.
			/// </summary>
			virtual void Initialize(const unsigned int program) = 0;

			/// <summary>
			/// Binds the buffer to be used by GPU.
			/// </summary>
			virtual void Bind() = 0;

			/// <summary>
			/// Unbinds the buffer.
			/// </summary>
			virtual void Unbind();

			/// <summary>
			/// Deletes the buffer from GPU memory.
			/// </summary>
			virtual void DeleteBuffer();

			/// <summary>
			/// Destroy the buffer, alongside it's memory.
			/// </summary>
			virtual void Destroy() = 0;
		};
	}
}

#endif // !BASE_BUFFER_H