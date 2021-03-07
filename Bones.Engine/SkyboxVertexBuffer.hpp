#pragma once

#ifndef SKYBOX_VERTEX_BUFFER_H

#define SKYBOX_VERTEX_BUFFER

#include "VertexBuffer.hpp"
#include "utils.h"

namespace Bones
{
    namespace Buffers
    {
        class SkyboxVertexBuffer final : public VertexBuffer
        {
          

        public:
            SkyboxVertexBuffer() : VertexBuffer() 
            {
                const F32 data[108] = {
                    // positions          
                     -1.0f,  1.0f, -1.0f,
                     -1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f,  1.0f, -1.0f,
                     -1.0f,  1.0f, -1.0f,

                     -1.0f, -1.0f,  1.0f,
                     -1.0f, -1.0f, -1.0f,
                     -1.0f,  1.0f, -1.0f,
                     -1.0f,  1.0f, -1.0f,
                     -1.0f,  1.0f,  1.0f,
                     -1.0f, -1.0f,  1.0f,

                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,

                     -1.0f, -1.0f,  1.0f,
                     -1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f,
                     -1.0f, -1.0f,  1.0f,

                     -1.0f,  1.0f, -1.0f,
                      1.0f,  1.0f, -1.0f,
                      1.0f,  1.0f,  1.0f,
                      1.0f,  1.0f,  1.0f,
                     -1.0f,  1.0f,  1.0f,
                     -1.0f,  1.0f, -1.0f,

                     -1.0f, -1.0f, -1.0f,
                     -1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f, -1.0f,
                      1.0f, -1.0f, -1.0f,
                     -1.0f, -1.0f,  1.0f,
                      1.0f, -1.0f,  1.0f
                };
                m_name = "Skybox Vertex Buffer";
                m_attributeLocation = 0;
                m_structSize = 3;
                m_count = 108;
                m_structComponentLength = sizeof(F32);
                m_length = m_count * m_structSize * m_structComponentLength;
                m_structLength = m_structComponentLength * m_structSize;

                Bones::Utils::ArrayPtrToVectorData(data, m_count, m_data);
            };
        };
    }
}

#endif // !SKYBOX_VERTEX_BUFFER_H