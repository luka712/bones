VERTEX_SHADER
#version 300 es

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoords;

out vec2 v_texCoords;

void main()
{
    gl_Position = vec4(a_position, 0., 1.);
    v_texCoords = a_texCoords;
}

FRAGMENT_SHADER
#version 300 es

precision mediump float;

in vec2 v_texCoords;

uniform sampler2D u_screenTexture;

out vec4 color;

const float offset = 1.0 / 300.0;

void main()
{
    vec2 offsets[9];
    offsets[0] = vec2(-offset, offset); // top-left
    offsets[1] = vec2(0.0, offset); // top-center
    offsets[2] = vec2(offset, offset); // top-right
    offsets[3] = vec2(-offset, 0.0); // center-left
    offsets[4] = vec2(0.0, 0.0); // center-center
    offsets[5] = vec2(offset, 0.0); // center-right
    offsets[6] = vec2(-offset, -offset); // bottom-left
    offsets[7] = vec2(0.0, -offset); // bottom-center
    offsets[8] = vec2(offset, -offset); // bottom-right


    float kernel[9];
    kernel[0] = 1.;
    kernel[1] = 1.;
    kernel[2] = 1.;
    kernel[3] = 1.;
    kernel[4] = -8.;
    kernel[5] = 1.;
    kernel[6] = 1.;
    kernel[7] = 1.;
    kernel[8] = 1.;

    vec3 sampleTex[9];
    for (int i = 0; i < 9; i++)
    {
        sampleTex[i] = vec3(texture(u_screenTexture, v_texCoords.st + offsets[i]));
    }

    vec3 col = vec3(0.0);
    for (int i = 0; i < 9; i++)
    {
        col += sampleTex[i] * kernel[i];
    }

    color = vec4(col, 1.0);
}