#pragma once

#ifndef MATERIAL_STRUCTS_H

#define MATERIAL_STRUCTS_H

typedef unsigned long standard_material_options;

const standard_material_options STANDARD_MATERIAL_DISABLE_LIGHTS = 1UL << 0;
const standard_material_options STANDARD_MATERIAL_DISABLE_DIRECTIONAL_LIGHTS = 1UL << 1;
const standard_material_options STANDARD_MATERIAL_DISABLE_OMNI_DIRECTIONAL_LIGHTS = 1UL << 2;
const standard_material_options STANDARD_MATERIAL_DISABLE_SHADOWS = 1UL << 3;
const standard_material_options STANDARD_MATERIAL_DISABLE_DIRECTIONAL_SHADOWS = 1UL << 4;
const standard_material_options STANDARD_MATERIAL_DISABLE_OMNI_DIRECTIONAL_SHADOWS = 1UL << 5;
const standard_material_options STANDARD_MATERIAL_USE_DIFFUSE_MAP = 1UL << 6;
const standard_material_options STANDARD_MATERIAL_USE_SPECULAR_MAP = 1UL << 7;
const standard_material_options STANDARD_MATERIAL_USE_REFLECTION_MAP = 1UL << 8;

namespace Bones
{
	namespace Materials
	{
		/// <summary>
		/// The material shader options.
		/// </summary>
		struct StandardMaterialOptions final
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

			const standard_material_options ConvertToBits() const noexcept
			{
				return ConvertToUL();
			}
		};
	}
}

#endif // !MATERIAL_STRUCTS_H