#pragma once

#ifndef INTERLEAVED_BUFFER_H

#define INTERLEAVED_BUFFER_H

#include <string>
#include <iostream>
#include <vector>
#include "BaseBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		using namespace std;

		/// <summary>
		/// The description of buffer attributues.
		/// </summary>
		struct BufferAttribute 
		{
			I32 m_attributeLocation;			
			I32 m_size;
			I32 m_offset;
			string m_attributeLayoutName;
		};

		/// <summary>
		/// The interleaved buffer, which is buffer 
		/// that can contain multiple layout attributes in single memory
		/// Interleaved buffer represents "Structure of arrays" https://en.wikipedia.org/wiki/AoS_and_SoA
		/// For example 
		/// </summary>
		class InterleavedBuffer : public BaseBuffer
		{		
		public:
			/// <summary>
			/// Create the buffer.
			/// </summary>
			/// <param name="data">Data to be loaded to GPU.</param>
			/// <param name="length">Length of data to be loaded to GPU.</param>
			/// <param name="attributes">Description of layout attributes, such as positions, texuture coordinates etc...</param>
			InterleavedBuffer(const F32 *data, const I32 length, vector<BufferAttribute> attributes);

			void Initialize();

			/// <summary>
			/// Initialize for certain program.
			/// Program being collection of shaders.
			/// </summary>
			/// <param name="program">The shader program id.</param>
			void Initialize(const U32 program);
			void Bind();
			void Destroy();

			inline const std::string Type() const noexcept { return "interleaved_buffer"; }
		protected:
			const F32* m_data;
			vector<BufferAttribute> m_attributes;
			const std::string m_initializeEventName = "interleaved_buffer.initialized";
			const std::string m_destroyEventName = "interleaved_buffer.destroyed";
		};
	}
}

#endif // !INTERLEAVED_BUFFER_H