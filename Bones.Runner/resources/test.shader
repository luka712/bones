VERTEX_SHADER
#version 300 es

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
    gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);
    v_texCoords = a_texCoords;

    // transpose(inverse()) solves rotated and skewed models.
    v_normal = mat3(transpose(inverse(u_transform))) * a_normal;

    // pass fragment to apply lights and specular color to.
    v_fragPos = (u_transform * vec4(a_position, 1.0)).xyz;
}

FRAGMENT_SHADER
#version 300 es

precision mediump float;

const int MAX_DIRECTIONAL_LIGHTS = 5;
const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;

in vec2 v_texCoords;
in vec3 v_normal;
in vec3 v_fragPos;

out vec4 color;

struct Light
{
    float intensity;
    vec3 color;
};

// ambient light
struct AmbientLight
{
    Light base;
};
uniform AmbientLight u_ambientLight;

// directional light
struct DirectionalLight
{
    Light base;
    vec3 direction;
};
uniform DirectionalLight u_directionalLights[MAX_DIRECTIONAL_LIGHTS];
uniform int u_directionalLightsCount;

// point light
struct PointLight
{
    Light base;
    vec3 position;
    float constant;
    float linear;
    float exponent;
};
uniform PointLight u_pointLights[MAX_POINT_LIGHTS];
uniform int u_pointLightsCount;

struct SpotLight
{
    PointLight base;
    vec3 direction;
    float edge;
};
uniform SpotLight u_spotLights[MAX_SPOT_LIGHTS];
uniform int u_spotLightsCount;

uniform vec3 u_eyePosition;

struct Material
{
    float shininess;
    float intensity;
};
uniform Material u_material;

uniform sampler2D u_tex;

vec4 CalculateDirectionalLight(Light light, vec3 direction)
{
    // directionl light
    vec3 nDirection = normalize(direction);
    vec3 nNormal = -normalize(v_normal);
    float diffuseFactor = max(dot(nNormal, nDirection), 0.0);
    vec4 directionColor = vec4(light.color, 1.0) * light.intensity * diffuseFactor;

    // specular light 
    diffuseFactor = max(diffuseFactor, 0.0);

    vec3 fragToEye = normalize(u_eyePosition - v_fragPos);
    vec3 reflectedVertex = normalize(reflect(nDirection, nNormal));

    float specularFactor = max(dot(fragToEye, reflectedVertex), 0.0);
    specularFactor = pow(specularFactor, u_material.shininess);
    vec4 specularColor = vec4(light.color * u_material.intensity * specularFactor, 1.0);

    return directionColor + specularColor;
}

vec4 CalculatePointLight(PointLight pointLight)
{
    vec3 direction = v_fragPos - pointLight.position;
    float distance = length(direction);

    vec4 color = CalculateDirectionalLight(pointLight.base, direction);
    float attenuation = pointLight.exponent * distance * distance
        + pointLight.linear * distance
        + pointLight.constant;
    return color / attenuation;
}

vec4 GetAmbientLight()
{
    return vec4(u_ambientLight.base.color * u_ambientLight.base.intensity, 1.0);
}

vec4 GetDirectionalLights()
{
    vec4 finalColor = vec4(0.0);
    for (int i = 0; i < u_directionalLightsCount; i++)
    {
        finalColor += CalculateDirectionalLight(u_directionalLights[i].base, u_directionalLights[i].direction);
    }
    return finalColor;
}

vec4 GetPointLights()
{
    vec4 finalColor = vec4(0.0);
    for (int i = 0; i < u_pointLightsCount; i++)
    {
        finalColor += CalculatePointLight(u_pointLights[i]);
    }
    return finalColor;
}

vec4 GetSpotLights()
{
    vec4 finalColor = vec4(0.0);
    for (int i = 0; i < u_spotLightsCount; i++)
    {
        SpotLight spotLight = u_spotLights[i];
        float slFactor = dot(normalize(v_fragPos - spotLight.base.position), normalize(spotLight.direction));

        if (slFactor > spotLight.edge)
        {
            finalColor += CalculatePointLight(spotLight.base) * (1.0f - (1.0f - slFactor) * (1.0f / (1.0f - spotLight.edge)));
        }
    }
    return finalColor;
}

void main()
{
    color = texture(u_tex, v_texCoords) * (GetAmbientLight() + GetDirectionalLights() + GetPointLights() + GetSpotLights());
}