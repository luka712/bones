VERTEX_SHADER
#version 460

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec3 a_normal;

out vec2 v_texCoords;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_transform;

void main()
{
    // default mvp matrix
    gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);

    v_texCoords = a_texCoords;
}

FRAGMENT_SHADER
#version 460

#define USE_DIFFUSE_MAP ##DIFFUSE_MAP##

precision mediump float;

in vec2 v_texCoords;

struct Material
{
    vec4 diffuseColor;
#if USE_DIFFUSE_MAP
    sampler2D diffuseTexture;
#endif 
};
uniform Material u_material;

out vec4 color;

void main()
{
    vec4 baseColor = vec4(1.0);
#if USE_DIFFUSE_MAP
    baseColor = texture(u_material.diffuseTexture, v_texCoords);
#endif 
    color = baseColor * u_material.diffuseColor;
}