#pragma once

#ifndef MATERIAL_SHADER_STRUCTS_H

#define MATERIAL_SHADER_STRUCTS_H

typedef unsigned long material_shader_options;

const material_shader_options MATERIAL_SHADER_DISABLE_LIGHTS = 1UL << 0;
const material_shader_options MATERIAL_SHADER_DISABLE_DIRECTIONAL_LIGHTS = 1UL << 1;
const material_shader_options MATERIAL_SHADER_DISABLE_OMNI_DIRECTIONAL_LIGHTS = 1UL << 2;
const material_shader_options MATERIAL_SHADER_DISABLE_SHADOWS = 1UL << 3;
const material_shader_options MATERIAL_SHADER_DISABLE_DIRECTIONAL_SHADOWS = 1UL << 4;
const material_shader_options MATERIAL_SHADER_DISABLE_OMNI_DIRECTIONAL_SHADOWS = 1UL << 5;
const material_shader_options MATERIAL_SHADER_USE_DIFFUSE_MAP = 1UL << 6;
const material_shader_options MATERIAL_SHADER_USE_SPECULAR_MAP = 1UL << 7;
const material_shader_options MATERIAL_SHADER_USE_REFLECTION_MAP = 1UL << 8;

namespace Bones
{
	namespace Shaders
	{
		namespace Material
		{
			/// <summary>
			/// The material locations. There is only 1 material per shader instance.
			/// </summary>
			struct MaterialLocations
			{
				int specularIntensityLocation = -1;
				int specularShininessLocation = -1;
				int diffuseColorLocation = -1;
				int diffuseMapLocation = -1;
				int specularMapLocation = -1;
				int reflectionMapLocation = -1;
			};

			/// <summary>
			/// The ambient light locations. There is only 1 ambient light per shader instance.
			/// </summary>
			struct AmbientLightLocations
			{
				int colorLocation = -1;
			};

			/// <summary>
			/// The directional light locations. There are multiple directional lights per shader instance.
			/// </summary>
			struct DirectionalLightLocations : AmbientLightLocations
			{
				int directionLocation = -1;
				int specularColorLocation = -1;
				/// <summary>
				/// Projection * View of directional light.
				/// </summary>
				int projectionViewLocation = -1;
				/// <summary>
				/// Shadow map texture location.
				/// </summary>
				int shadowMapTextureLocation = -1;
			};


			/// <summary>
			/// The point light locations. There are multiple point lights per shader instance.
			/// </summary>
			struct PointLightLocations : AmbientLightLocations
			{
				struct Attenuation {
					int quadtraticLocation = -1;
					int linearLocation = -1;
					int constantLocation = -1;
				} attenuation;
				int positionLocation = -1;
				int specularColorLocation = -1;

				//int shadowMapLocation = -1;
				//int farPlaneLocation = -1;
				//int shadowMapTextureLocation = -1;
			};

			/// <summary>
			/// The spot light locations. There are mutliple spot lights per shader intsance.
			/// </summary>
			struct SpotLightLocations : PointLightLocations
			{
				int directionLocation = -1;
				int cutOffLocation = -1;
				int outerCutOffLocation = -1;
			};

			/// <summary>
			/// The material shader options.
			/// </summary>
			struct MaterialShaderOptions final
			{
				bool disableLights = false;
				bool disableDirectionalLights = false;
				bool disableOmniDirectionalLights = false;
				bool disableShadows = false;
				bool disableDirectionalShadows = false;
				bool disableOmniDirectionalShadows = false;
				bool useDiffuseMap = false;
				bool useSpecularMap = false;
				bool useReflectionMap = false;

				const unsigned long ConvertToUL() const noexcept
				{
					unsigned long bin = 0;

					if (disableLights) bin ^= 1UL << 0;
					if (disableDirectionalLights) bin ^= 1UL << 1;
					if (disableOmniDirectionalLights) bin ^= 1UL << 2;
					if (disableShadows) bin ^= 1UL << 3;
					if (disableDirectionalShadows) bin ^= 1UL << 4;
					if (disableOmniDirectionalShadows) bin ^= 1UL << 5;
					if (useDiffuseMap) bin ^= 1UL << 6;
					if (useSpecularMap) bin ^= 1UL << 7;
					if (useReflectionMap) bin ^= 1UL << 8;

					return bin;
				}

				const material_shader_options ConvertToBits() const noexcept
				{
					return ConvertToUL();
				}
			};

		}
	}
}

#endif // !MATERIAL_SHADER_STRUCTS_H