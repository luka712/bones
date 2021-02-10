VERTEX_SHADER
#version 460

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec3 a_normal;

out vec2 v_texCoords;
out vec3 v_normal;
out vec3 v_fragPos;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_transform;

void main()
{
    // default mvp matrix
    vec4 fragment = u_transform * vec4(a_position, 1.);
    gl_Position = u_projection * u_view * fragment;

    v_texCoords = a_texCoords;
    v_normal = mat3(transpose(inverse(u_transform))) * a_normal;
    v_fragPos = fragment.xyz;
}

FRAGMENT_SHADER
#version 460

#define USE_LIGHTS ##USE_LIGHTS## 
#define USE_DIFFUSE_MAP ##DIFFUSE_MAP##
#define USE_SPECULAR_MAP ##SPECULAR_MAP##
#define USE_REFLECTION_MAP ##REFLECTION_MAP##
#define MAX_DIRECTIONAL_LIGHTS ##MAX_DIRECTIONAL_LIGHTS##
#define MAX_POINT_LIGHTS ##MAX_POINT_LIGHTS##
#define MAX_SPOT_LIGHTS ##MAX_SPOT_LIGHTS##
#define DISCARD_THRESHOLD 0.05

precision mediump float;

in vec2 v_texCoords;
in vec3 v_normal;
in vec3 v_fragPos;

#if (USE_LIGHTS | USE_SPECULAR_MAP)
uniform vec3 u_eyePosition;
#endif 

struct Material
{
    vec4 diffuseColor;
#if USE_DIFFUSE_MAP
    sampler2D diffuseMap;
#endif 
#if USE_SPECULAR_MAP
    sampler2D specularMap;
#endif 
#if USE_REFLECTION_MAP
    samplerCube reflectionMap;
#endif 

#if USE_LIGHTS
    float shininess;
#endif 
};
uniform Material u_material;

#if USE_LIGHTS
struct Light
{
    vec3 color;
};
uniform Light u_ambientLight;

struct DirectionalLight
{
    Light base;
    vec3 direction;
    vec3 specularColor;
};
uniform DirectionalLight u_directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform int u_directionalLightsCount;

struct PointLight
{
    DirectionalLight base;

    vec3 position;

    float constant;
    float linear;
    float quadtratic;
};
uniform PointLight u_pointLights[MAX_POINT_LIGHTS];
uniform int u_pointLightsCount;

struct SpotLight
{
    PointLight base;

    float cutOff;
    float outerCutOff;
};
uniform SpotLight u_spotLights[MAX_SPOT_LIGHTS];
uniform int u_spotLightsCount;

#endif 

out vec4 finalColor;

#if USE_LIGHTS
vec3 processAmbientLight(Light light, vec4 color);
vec3 processDirectionalLight(DirectionalLight light, vec3 nNormal, vec3 lightDir, vec3 viewDir, vec4 diffuseColor, vec4 specularColor);
vec3 processPointLight(PointLight light, vec3 nNormal, vec3 lightDir, vec3 viewDir, vec4 diffuseColor, vec4 specularColor);
vec3 processSpotLight(SpotLight light, vec3 nNormal, vec3 lightDir, vec3 viewDir, vec4 diffuseColor, vec4 specularColor);
#endif 

#if USE_REFLECTION_MAP

vec4 reflectionMap();

#endif

void main()
{
    finalColor = vec4(1.0);
    vec4 diffuseColor = vec4(1.0);
#if USE_DIFFUSE_MAP
    diffuseColor = texture(u_material.diffuseMap, v_texCoords);
#elif USE_REFLECTION_MAP
    diffuseColor = reflectionMap();
#else 
    diffuseColor = u_material.diffuseColor;
#endif 

    //// discard fragments for really small alpha values.
    if (diffuseColor.a < DISCARD_THRESHOLD)
        discard;

#if USE_LIGHTS
    vec3 color = processAmbientLight(u_ambientLight, diffuseColor);

    vec3 nNormal = normalize(v_normal);
    vec3 viewDir = normalize(u_eyePosition - v_fragPos);

    int count = min(u_directionalLightsCount, MAX_DIRECTIONAL_LIGHTS);
#if USE_SPECULAR_MAP
    vec4 specularMap = texture(u_material.specularMap, v_texCoords);
#endif 
    for (int i = 0; i < count; i++)
    {
        vec3 lightDir = normalize(-u_directionalLights[i].direction);
#if USE_SPECULAR_MAP
        color += processDirectionalLight(u_directionalLights[i], nNormal, lightDir, viewDir, diffuseColor, specularMap);
#else 
        color += processDirectionalLight(u_directionalLights[i], nNormal, lightDir, viewDir, diffuseColor, diffuseColor);
#endif 

    }

    count = min(u_pointLightsCount, MAX_POINT_LIGHTS);
    for (int i = 0; i < count; i++)
    {
        vec3 lightDir = normalize(u_pointLights[i].position - v_fragPos);
#if USE_SPECULAR_MAP
        color += processPointLight(u_pointLights[i], nNormal, lightDir, viewDir, diffuseColor, specularMap);
#else 
        color += processPointLight(u_pointLights[i], nNormal, lightDir, viewDir, diffuseColor, diffuseColor);
#endif 
    }

    count = min(u_spotLightsCount, MAX_SPOT_LIGHTS);
    for (int i = 0; i < count; i++)
    {
        vec3 lightDir = normalize(u_spotLights[i].base.position - v_fragPos);
#if USE_SPECULAR_MAP
        color += processSpotLight(u_spotLights[i], nNormal, lightDir, viewDir, diffuseColor, specularMap);
#else 
        color += processSpotLight(u_spotLights[i], nNormal, lightDir, viewDir, diffuseColor, diffuseColor);
#endif 
    }

    finalColor = vec4(color, diffuseColor.a);
#else 
    finalColor = diffuseColor;
#endif 
}

#if USE_LIGHTS
vec3 processAmbientLight(Light light, vec4 diffuseColor)
{
    return u_ambientLight.color * diffuseColor.xyz;
}

vec3 processDirectionalLight(DirectionalLight light, vec3 nNormal, vec3 lightDir, vec3 viewDir, vec4 diffuseColor, vec4 specularColor)
{
    float diffFactor = max(dot(nNormal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, nNormal);

    float specularFactor = pow(max(dot(viewDir, reflectDir), 0.0), u_material.shininess);

    vec3 diffuse = diffFactor * light.base.color * diffuseColor.xyz;
    vec3 specular = specularFactor * light.specularColor * specularColor.xyz;

    return diffuse + specular;
}

vec3 processPointLight(PointLight light, vec3 nNormal, vec3 lightDir, vec3 viewDir, vec4 diffuseColor, vec4 specularColor)
{
    vec3 lightAmount = processDirectionalLight(light.base, nNormal, lightDir, viewDir, diffuseColor, specularColor);

    // distance
    float d = length(light.position - v_fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * d + light.quadtratic * d * d);

    return lightAmount * attenuation;
}

vec3 processSpotLight(SpotLight light, vec3 nNormal, vec3 lightDir, vec3 viewDir, vec4 diffuseColor, vec4 specularColor)
{
    vec3 color = processPointLight(light.base, nNormal, lightDir, viewDir, diffuseColor, specularColor);

    float theta = dot(lightDir, normalize(-light.base.base.direction));
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    return color * intensity;
}

#endif

#if USE_REFLECTION_MAP

vec4 reflectionMap()
{
    vec3 viewDir = normalize(v_fragPos - u_eyePosition);
    vec3 r = reflect(viewDir, normalize(v_normal));
    return vec4(texture(u_material.reflectionMap, -r).rgb, 1.0);
}

#endif 