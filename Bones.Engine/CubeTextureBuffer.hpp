#pragma once

#include "VertexBuffer.hpp"
#include "utils.h"

namespace Bones
{
    namespace Buffers
    {
        class CubeTextureBuffer final : public VertexBuffer
        {
          

        public:
            CubeTextureBuffer() : VertexBuffer() 
            {
                const F32 data[48] = {
                    // Front
                    0.0,  0.0,
                    1.0,  0.0,
                    1.0,  1.0,
                    0.0,  1.0,
                    // Back
                    0.0,  0.0,
                    1.0,  0.0,
                    1.0,  1.0,
                    0.0,  1.0,
                    // Top
                    0.0,  0.0,
                    1.0,  0.0,
                    1.0,  1.0,
                    0.0,  1.0,
                    // Bottom
                    0.0,  0.0,
                    1.0,  0.0,
                    1.0,  1.0,
                    0.0,  1.0,
                    // Right
                    0.0,  0.0,
                    1.0,  0.0,
                    1.0,  1.0,
                    0.0,  1.0,
                    // Left
                    0.0,  0.0,
                    1.0,  0.0,
                    1.0,  1.0,
                    0.0,  1.0,
                };
                m_name = "Cube Texture Buffer";
                m_layoutName = "a_texCoords";
                m_count = 48;
                m_structSize = 2;
                m_structComponentLength = sizeof(F32);
                m_structLength = m_structComponentLength * m_structSize;
                m_countOfStructs = m_count / m_structSize;

                Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
                m_length = m_data.size();
            }
        };
    }
}
