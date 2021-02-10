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

void main()
{
    color = texture(u_screenTexture, v_texCoords);
    color.rgb = vec3(dot(color.rgb, vec3(0.2126, 0.7152, 0.0722)));
}