VERTEX_SHADER
#version 460 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_transform;

void main()
{
    gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);
}

FRAGMENT_SHADER
#version 460 core

precision mediump float;

uniform vec4 u_color;

out vec4 color;

void main()
{
    color = u_color;
}