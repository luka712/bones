VERTEX_SHADER
#version 460 core

layout(location = 0) in vec2 a_position;
layout(location = 1) in vec2 a_texCoords;

out vec2 v_texCoords;

void main()
{
    gl_Position = vec4(a_position, 0., 1.);
    v_texCoords = a_texCoords;
}

FRAGMENT_SHADER
#version 460 core

precision mediump float;

in vec2 v_texCoords;

uniform sampler2D u_screenTexture;

out vec4 color;

const float offset = 1.0 / 300.0;

void main()
{
    vec2 offsets[9] = vec2[]
    (
        vec2(-offset, offset), // top-left
        vec2(0.0, offset), // top-center
        vec2(offset, offset), // top-right
        vec2(-offset, 0.0), // center-left
        vec2(0.0, 0.0), // center-center
        vec2(offset, 0.0), // center-right
        vec2(-offset,-offset), // bottom-left
        vec2(0.0, -offset), // bottom-center
        vec2(offset, -offset) // bottom-right
    );

    float kernel[9] = float[] 
    (
        0, -1, 0,
       -1,  5, -1,
        0, -1, 0
    );


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