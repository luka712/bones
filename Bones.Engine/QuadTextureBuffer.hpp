#pragma once

#include "VertexBuffer.hpp"
#include "utils.h"

namespace Bones
{
	namespace Buffers
	{

		/// <summary>
		/// QuadVertexBuffer 
		/// </summary>
		class QuadTextureBuffer final : public VertexBuffer
		{
			

		public:
			/// <summary>
			/// The constructors for QuadTextureBuffer
			/// </summary>
			/// <returns>QuadTextureBuffer</returns>
			QuadTextureBuffer() : VertexBuffer() 
			{
				const F32 data[8] = {
				   1.0f, 1.0f,
					0.0f, 1.0f,
					1.0f, 0.0f,
				   0.0f, 0.0f,
				};
				m_name = "Quad Texture Buffer";
				m_layoutName = "a_texCoords";
				m_count = 8;
				m_structSize = 2;
				m_structLength = m_structComponentLength * m_structSize;

				Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
				m_length = m_data.size();
			}
		};
	}
}
