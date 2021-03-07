#pragma once

#include "VertexBuffer.hpp"


namespace Bones
{
    namespace Buffers
    {
        /// <summary>
        /// The cube vertex buffer.
        /// </summary>
        class CubeVertexBuffer final : public VertexBuffer
        {
          
        public:
            CubeVertexBuffer() : VertexBuffer()
            {
                const float data[72] = {
                    // Front face
                  -1.0, -1.0,  1.0,
                   1.0, -1.0,  1.0,
                   1.0,  1.0,  1.0,
                  -1.0,  1.0,  1.0,

                  // Back face
                  -1.0, -1.0, -1.0,
                  -1.0,  1.0, -1.0,
                   1.0,  1.0, -1.0,
                   1.0, -1.0, -1.0,

                   // Top face
                   -1.0,  1.0, -1.0,
                   -1.0,  1.0,  1.0,
                    1.0,  1.0,  1.0,
                    1.0,  1.0, -1.0,

                    // Bottom face
                    -1.0, -1.0, -1.0,
                     1.0, -1.0, -1.0,
                     1.0, -1.0,  1.0,
                    -1.0, -1.0,  1.0,

                    // Right face
                     1.0, -1.0, -1.0,
                     1.0,  1.0, -1.0,
                     1.0,  1.0,  1.0,
                     1.0, -1.0,  1.0,

                     // Left face
                     -1.0, -1.0, -1.0,
                     -1.0, -1.0,  1.0,
                     -1.0,  1.0,  1.0,
                     -1.0,  1.0, -1.0,
                };

                m_name = "Cube Vertex Buffer";
                m_layoutName = "a_position";
                m_count = 72;
                m_structSize = 3;
                m_structComponentLength = sizeof(F32);
                m_structLength = m_structComponentLength * m_structSize;
                m_countOfStructs = m_count / m_structSize;
                
                Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
                m_length = m_data.size();
            };
        };
    }
}