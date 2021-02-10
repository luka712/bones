#pragma once

#include "VertexBuffer.hpp"


namespace Bones
{
    namespace Buffers
    {
        class CubeVertexBuffer final : public VertexBuffer
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

        public:
            CubeVertexBuffer() : VertexBuffer("a_position", 3, data, 72) {};
        };
    }
}