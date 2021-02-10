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

void main()
{
    color = vec4(vec3(1.0 - texture(u_screenTexture, v_texCoords).rgb), 1.0);
}