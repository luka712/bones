#pragma once

#ifndef BASE_BUFFER_H

#define BASE_BUFFER_H

#include "IEntity.hpp"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// Base abstract representation of buffer, from which all others inherit from.
		/// IndexBuffer, InterleavedBuffer and VertexBuffer inherit from BaseBuffer.
		/// </summary>
		class BaseBuffer : public IEntity
		{
		public:
			/// <summary>
			/// Constructor.
			/// </summary>
			BaseBuffer();

			// count of elements in array. To not be confused with length.
			// For example length might be 8 for indices of unsigned shorts ( 2 bytes per elemt ). Therefore count is 4.
			U32 m_count = 0;

			// total length of buffer. To not be confused with count.
			// For example count might be 4 for indices of unsigned shorts. But length will be 8 since count * sizeof(unsigned short) is 8.
			U32 m_length = 0;

			/// <summary>
			/// The load. In case of buffer attributes, actually does nothing.
			/// </summary>
			void Load() override;

			/// <summary>
			/// The initialize method, which creates buffer instance loads data to memory for specific program.
			/// </summary>
			virtual void Initialize(const U32 program) = 0;

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

		protected:
			// The address of buffer in GPU.
			U32 m_buffer = 0;

			/// <summary>
			/// Creates base data representation for events.
			/// </summary>
			virtual std::unordered_map<std::string, Bones::Variant> CreateEventData();
		};
	}
}

#endif // !BASE_BUFFER_H