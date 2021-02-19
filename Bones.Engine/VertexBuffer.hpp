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
			/// <summary>
			/// The constructor.
			/// </summary>
			/// <param name="layoutName">Layout name as specified in shader.</param>
			/// <param name="size">The size of vertex. For vec3 pass 3, for vec2 pass 2 etc...</param>
			/// <param name="data">The data</param>
			/// <param name="length">The length of array. Number of vertices in data array.</param>
			VertexBuffer(const std::string& layoutName, const I32 size, const F32* data, const U64 length);

			/// <summary>
			/// The constructor.
			/// </summary>
			/// <param name="layoutName">Attribute location as specified by shader (layout = 0), (layout = 1) etc.</param>
			/// <param name="size">The size of vertex. For vec3 pass 3, for vec2 pass 2 etc...</param>
			/// <param name="data">The data</param>
			/// <param name="length">The length of array. Number of vertices in data array.</param>
			VertexBuffer(const I32 attributeLocation, const I32 size, const F32* data, const U64 length);


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
			I32 m_size = 0;
			I32 m_attributeLocation = -1;
			
			const F32 *m_data;

			std::string m_layoutName;
			const std::string m_initializeEventName = "vertex_bufer.initialized";
			const std::string m_destroyEventName = "vertex_bufer.destroyed";
		};
	}
}
