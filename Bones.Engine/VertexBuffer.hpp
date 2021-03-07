#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "BaseBuffer.hpp"

namespace Bones
{
	namespace Buffers
	{
		/// <summary>
		/// The vertex buffer which is used to represent positions, texture coordinates, normals coordinates
		/// which are sent to GPU. Opposed to interleaved buffer, this buffer only represent single piece of data
		/// for layout attribute. It could be only positions, or only texture, or only normals etc...
		/// </summary>
		class VertexBuffer : public BaseBuffer
		{

		public:
			// Number of total elements. For example 2 vec3 will be 6 for m_count, but 2 for m_countOfStructs
			U32 m_countOfStructs = 0;
			// Size of elements in vertex
			U32 m_structSize = 0;
			// component length. For example vec3 is 3 * 4 = 12 or 3 * sizeof(F32)
			U32 m_structLength = 0;
			// Attribute layout location.
			I32 m_attributeLocation = -1;

			// Byte size of element 
			U32 m_structComponentLength = 0;

			// Data
			std::vector<U8> m_data;

			// Attribute layout name 
			std::string m_layoutName = "";

			/// <summary>
			/// The constructor.
			/// </summary>
			/// <param name="layoutName">Layout name as specified in shader.</param>
			/// <param name="size">The size of vertex. For vec3 pass 3, for vec2 pass 2 etc...</param>
			/// <param name="data">The data</param>
			/// <param name="length">The count of elements of array. Number of vertices in data array.</param>
			VertexBuffer(const std::string& layoutName, const I32 size, const F32* data, const U64 countOfElements);

			/// <summary>
			/// The constructor.
			/// </summary>
			/// <param name="layoutName">Attribute location as specified by shader (layout = 0), (layout = 1) etc.</param>
			/// <param name="size">The size of vertex. For vec3 pass 3, for vec2 pass 2 etc...</param>
			/// <param name="data">The data</param>
			/// <param name="length">The count of elements  of array. Number of vertices in data array.</param>
			VertexBuffer(const I32 attributeLocation, const I32 size, const F32* data, const U64 countOfElements);


			void Initialize() override;

			/// <summary>
			/// The initialize method.
			/// </summary>
			/// <param name="program">The id of glProgram.</param>
			void Initialize(const U32 program) override;
			void Bind() override ;

			void Destroy();

			inline const std::string Type() const noexcept { return "vertex_bufer"; }

		protected:
			const std::string m_initializeEventName = "vertex_bufer.initialized";
			const std::string m_destroyEventName = "vertex_bufer.destroyed";

			VertexBuffer();
		};
	}
}
