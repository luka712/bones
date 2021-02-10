VERTEX_SHADER
#version 460 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_projection;
uniform mat4 u_view;

out vec3 v_texCoords;

void main()
{
    v_texCoords = a_position;
    gl_Position = (u_projection * u_view * vec4(a_position, 1.)).xyww;
}

FRAGMENT_SHADER
#version 460 core

precision mediump float;

in vec3 v_texCoords;

uniform samplerCube u_texture;

out vec4 o_color;

void main()
{
    o_color = texture(u_texture, v_texCoords);
}