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
uniform sampler2D u_vignetteTexture;
uniform sampler2D u_scanLineTexture;
uniform sampler2D u_noiseTexture;

uniform float u_scanLineTileAmount = 4.0;
uniform float u_distortion = 0.2;
uniform float u_scale = 0.8;
uniform float u_random = 1.0;
uniform float u_time = 1.0;
uniform float u_brightness = 0.5;
uniform float u_contrast = 2.0;
uniform float u_vignetteIntensity = 1.0;
uniform float u_noiseIntensity = 1.0;
uniform float u_scanLineIntensity = 1.0;

uniform vec2 u_noiseSpeed = vec2(0.1, 0.1);
uniform vec3 u_nightVisionColor = vec3(0, 1, 0);

out vec4 color;

vec2 barrelDistortion(vec2 coord);
vec4 vignetteEffect();
vec4 noiseEffect();
vec4 scanLineEffect();

void main()
{
	vec2 distortedUV = barrelDistortion(v_texCoords);
	vec4 mainColor = texture(u_screenTexture, distortedUV);
	


	float lum = dot(vec3(0.299, 0.587, 0.114), mainColor.rgb);
	lum += u_brightness;
	// TODO: 
	color = lum * 2 + vec4(u_nightVisionColor, 1.0);

	color = vec4(pow(color.r, u_contrast), pow(color.g, u_contrast), pow(color.b, u_contrast), 1.0);
	color *= vignetteEffect();
	color *= noiseEffect();
	color *= scanLineEffect();
}

vec4 vignetteEffect()
{
	vec4 color = texture(u_vignetteTexture, v_texCoords);
	color.r = clamp(color.r + (1.0 - u_vignetteIntensity), 0.0, 1.0);
	color.g = clamp(color.g + (1.0 - u_vignetteIntensity), 0.0, 1.0);
	color.b = clamp(color.b + (1.0 - u_vignetteIntensity), 0.0, 1.0);
	return color;
}

vec4 noiseEffect()
{
	vec2 noiseUV = vec2(v_texCoords.x + (u_random * sin(u_time * 0.001) * u_noiseSpeed.x), v_texCoords.y + (u_time * u_noiseSpeed.y));
	vec4 color = texture(u_noiseTexture, noiseUV);

	// If intensity 0, multiplied color is 1.
	// if inensity 1, multiplied color is range (0,1) texel color
	// if intensity 0.5, noise is reduced
	color.r = 1.0 - (u_noiseIntensity * color.r);
	color.g = 1.0 - (u_noiseIntensity * color.g);
	color.b = 1.0 - (u_noiseIntensity * color.b);

	return color;
}

vec4 scanLineEffect()
{
	vec2 scanLinesUV = vec2(v_texCoords * u_scanLineTileAmount);
	vec4 color = texture(u_scanLineTexture, scanLinesUV);
	color.r = 1.0 - (u_scanLineIntensity * color.r);
	color.g = 1.0 - (u_scanLineIntensity * color.g);
	color.b = 1.0 - (u_scanLineIntensity * color.b);
	return color;
}

vec2 barrelDistortion(vec2 coord)
{
	// https://www.ssontech.com/content/lensalg.html
	vec2 c = coord.xy - vec2(0.5);
	float r2 = c.x * c.x + c.y * c.y;
	float f = 1.0 + r2 * (u_distortion * sqrt(r2));

	return f * u_scale * c + 0.5;
}
