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
			// Layout location 
			I32 m_attributeLocation;	
			// Size of struct, ie vec3 this should be 3
			U32 m_structSize;
			// Byte size of element. For float it should be 4
			U32 m_structComponentLength;
			// Offset in bytes. For example if previous is vec3, offset is 12. sizeof(vec3)
			U32 m_offsetLength;
			// Layout location name
			string m_attributeLayoutName;

			inline const U32 StructLength() const 
			{
				return m_structComponentLength * m_structSize;
			}
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
			// Size of stride, which is sum of attributes struct lengths.
			U32 m_strideLength = 0;
			// For stride of vec2, vec3 this is 5
			U32 m_strideComponentsSize = 0;

			std::vector<U8> m_data; 
			vector<BufferAttribute> m_attributes;

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
			InterleavedBuffer();

			const std::string m_initializeEventName = "interleaved_buffer.initialized";
			const std::string m_destroyEventName = "interleaved_buffer.destroyed";

	
		};
	}
}

#endif // !INTERLEAVED_BUFFER_H