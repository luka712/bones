VERTEX_SHADER
#version 460

layout(location = 0) in vec3 a_position;

uniform mat4 u_transform; // model transform
uniform mat4 u_directionalLightProjView; // light_projection * light_view , aka directional light space position

void main()
{
	gl_Position = u_directionalLightProjView * u_transform * vec4(a_position, 1.0);
}