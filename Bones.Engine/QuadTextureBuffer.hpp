#pragma once

#include "VertexBuffer.hpp"


namespace Bones
{
	namespace Buffers
	{

		/// <summary>
		/// QuadVertexBuffer 
		/// </summary>
		class QuadTextureBuffer final : public VertexBuffer
		{
			const F32 data[8] = {
				   1.0f, 1.0f,
					0.0f, 1.0f,
					1.0f, 0.0f,
				   0.0f, 0.0f,
			};

		public:
			/// <summary>
			/// The constructors for QuadTextureBuffer
			/// </summary>
			/// <returns>QuadTextureBuffer</returns>
			QuadTextureBuffer() : VertexBuffer("a_texCoords", 2, data, 8) 
			{
				m_name = "Quad Texture Buffer";
			}
		};
	}
}
