VERTEX_SHADER
#version 300 es

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec2 a_texCoords;
layout(location = 2) in vec3 a_normal;

out vec2 v_texCoords;
out vec3 v_normal;
out vec3 v_fragPos;
out vec4 v_directionalLightSpacePos;

uniform mat4 u_view;
uniform mat4 u_projection;
uniform mat4 u_transform;
uniform mat4 u_directionalLightProjView; // light_projection * light_view , aka directional light space position

void main()
{
    // default mvp matrix
    gl_Position = u_projection * u_view * u_transform * vec4(a_position, 1.);

    // light proj * light view * model transform * vertices for shadows 
    v_directionalLightSpacePos = u_directionalLightProjView * u_transform * vec4(a_position, 1.0);

    v_texCoords = a_texCoords;

    // transpose(inverse()) solves rotated and skewed models when using lights.
    v_normal = mat3(transpose(inverse(u_transform))) * a_normal;

    // pass fragment to apply lights and specular color to.
    v_fragPos = (u_transform * vec4(a_position, 1.0)).xyz;
}

FRAGMENT_SHADER
#version 300 es

// TODO: move to uniforms with should recompile flag ? no need to send these every time.
#define USE_SHADOWS 1 // should use shadows ? 
#define PCR 1 // percentage closer filtering ( for directional shadows ) 
#define PCR_QUALITY 3 // quality of pcr, can be 0,1,2. 0 has pass on self and divider is 1. 1 has 3 passes horizontally, 3 vertcally, therefore divider is 9

#if PCR
    #if PCR_QUALITY == 3
        #define PCR_PASS 3
        #define PCR_N 49.0
    #elif PCR_QUALITY == 2
        #define PCR_PASS 2
        #define PCR_N 25.0
    #elif PCR_QUALITY == 1
        #define PCR_PASS 1
        #define PCR_N 9.0
    #else
        #define PCR_PASS 0
        #define PCR_N 1.0
    #endif
#endif 

precision mediump float;

const int MAX_POINT_LIGHTS = 5;
const int MAX_SPOT_LIGHTS = 5;

in vec2 v_texCoords;
in vec3 v_normal;
in vec3 v_fragPos;
in vec4 v_directionalLightSpacePos;

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
uniform DirectionalLight u_directionalLight;

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
uniform sampler2D u_directionalShadowMapTex;


float DirectionalShadowFactor(DirectionalLight light)
{
    // projection is always divided by w component.
    vec3 pCoords = v_directionalLightSpacePos.xyz / v_directionalLightSpacePos.w;

    // move to center
    pCoords = (pCoords * 0.5) + 0.5;

    float currentDepth = pCoords.z;

    // if greater area shouldn't be in shadow, there is no projection over it. // out of texture bounds
    if (currentDepth > 1.0)
    {
        return float(0.0);
    }
  
    // values should be sligthly above of what's on shadow map to correct shadow acne 
    // https://digitalrune.github.io/DigitalRune-Documentation/html/3f4d959e-9c98-4a97-8d85-7a73c26145d7.htm
    // bias according to light angle as well
    float lightAngle = dot(normalize(v_normal), normalize(light.direction));
    float bias = max(0.05 * (1.0 - lightAngle ), 0.005);
    
    float shadow = 0.0;
#if PCR == 1

    // get texel size. 1.0 / textureSize where texture size is for example 1024. Can be passed instead.
    vec2 texelSize = vec2(1.0) / vec2(textureSize(u_directionalShadowMapTex, 0));
    for (int x = -PCR_PASS; x <= PCR_PASS; x++)
    {
        for (int y = -PCR_PASS; y <= PCR_PASS; y++)
        {
            float pcf = texture(u_directionalShadowMapTex, pCoords.xy + vec2(x, y) * texelSize).r;
            shadow += currentDepth - bias > pcf ? 1.0 : 0.0;
        }
    }

    // nine passes for PCR_QUALITY of 1 for 9 pixels. Middle one, and neighbouring ones.
    shadow /= PCR_N;

#else 
    // no filtering at all
    float closestDepth = texture(u_directionalShadowMapTex, pCoords.xy).r;  // always stored in first channel x or r
    shadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
#endif 

    return shadow;
}

vec4 CalculateDirectionalLight(Light light, vec3 direction, float shadowFactor)
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

    return (1.0 - shadowFactor) * (directionColor + specularColor);
}

vec4 CalculatePointLight(PointLight pointLight)
{
    vec3 direction = v_fragPos - pointLight.position;
    float distance = length(direction);

    vec4 color = CalculateDirectionalLight(pointLight.base, direction, 0.0);
    float attenuation = pointLight.exponent * distance * distance
        + pointLight.linear * distance
        + pointLight.constant;
    return color / attenuation;
}

vec4 GetAmbientLight()
{
    return vec4(u_ambientLight.base.color * u_ambientLight.base.intensity, 1.0);
}

vec4 GetDirectionalLight()
{
#if USE_SHADOWS == 1
     float shadowFactor = DirectionalShadowFactor(u_directionalLight);
#else
    float shadowFactor = 0.0;
#endif 
     return CalculateDirectionalLight(u_directionalLight.base, u_directionalLight.direction, shadowFactor);
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
    // 1 ambinet, 1 direction and multiple spot and point lights.
    color = texture(u_tex, v_texCoords) * (GetAmbientLight() + GetDirectionalLight() + GetPointLights() + GetSpotLights());
}