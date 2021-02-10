VERTEX_SHADER
#version 300 es

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texcoords;
layout(location = 2) in vec2 a_normal;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_transform;

out vec2 v_texcoords;

void main()
{
    v_texcoords = a_texcoords;
    gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);
}

FRAGMENT_SHADER
#version 300 es

precision mediump float;

in vec2 v_texcoords;

uniform sampler2D u_tex;

out vec4 color;

void main()
{
    color = texture2D(u_tex, v_texcoords);
}