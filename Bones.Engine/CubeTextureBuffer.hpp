#pragma once

#include "VertexBuffer.hpp"

namespace Bones
{
    namespace Buffers
    {
        class CubeTextureBuffer final : public VertexBuffer
        {
            const float data[48] = {
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

        public:
            CubeTextureBuffer() : VertexBuffer("a_texCoords",2, data, 64) 
            {
                m_name = "Cube Texture Buffer";
            }
        };
    }
}
