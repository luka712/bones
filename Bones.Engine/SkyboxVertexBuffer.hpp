#pragma once

#ifndef SKYBOX_VERTEX_BUFFER_H

#define SKYBOX_VERTEX_BUFFER

#include "VertexBuffer.hpp"


namespace Bones
{
    namespace Buffers
    {
        class SkyboxVertexBuffer final : public VertexBuffer
        {
            const float data[108] = {
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

        public:
            SkyboxVertexBuffer() : VertexBuffer(0, 3, data, 108) {};
        };
    }
}

#endif // !SKYBOX_VERTEX_BUFFER_H