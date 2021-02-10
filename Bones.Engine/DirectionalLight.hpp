#pragma once

#ifndef DIRECTIONAL_LIGHT_H

#define DIRECTIONAL_LIGHT_H 

#include "BaseLight.hpp"
//#include "DirectionalLightShadowMap.hpp"
#include "MaterialShader.hpp"

namespace  Bones
{
	namespace Shaders
	{
		namespace Material
		{
			struct DirectionalLightLocations;
		}
	}
}

using namespace glm;
using namespace Bones::Light;
using Bones::Shaders::Material::DirectionalLightLocations;

namespace Bones
{
	namespace Light
	{
		class DirectionalLight : public BaseLight
		{
		private:
			vec3 m_direction;
			// DirectionalLightShadowMap* m_shadowMap;

			// used for shadow maps
			mat4 m_projection, m_view, m_projectionView;
		public:
			vec3 m_specularColor = vec3(1, 1, 1);

			DirectionalLight();
			DirectionalLight(vec3 direction, vec3 color);
			DirectionalLight(vec3 direction, vec3 color, float intensity);

			void Initialize() override;

			// getters setters 
			const vec3& GetDirection() const noexcept { return m_direction; }
			void SetDirection(float x, float y, float z);

			/// <summary>
			/// Get the shadow map.
			/// </summary>
			/// <returns>ShadowMap*</returns>
			//DirectionalLightShadowMap* GetShadowMap() const noexcept { return m_shadowMap; }
			const glm::mat4 GetLightProjectionViewMatrix() const noexcept { return m_projectionView; }

			// methods 

			/// <summary>
			/// Offset from GL_TEXTURE0 for n places
			/// </summary>
			/// <param name="textureUnit">The texture unit. For example GL_TEXTURE0</param>
			/// <param name="offset">N places to offset from. For example 1 results in GL_TEXTURE0 + 1 ... GL_TEXTURE1.</param>
			//void ReadShadowMap(GLTextureUnit textureUnit ,unsigned int offset) const;

			/// <summary>
			/// Read the shadow map and pass it to texture unit.
			/// </summary>
			/// <param name="textureUnit">GLTextureUnit.TEXTURE0 as GL_TEXTURE0 ... which unit to bind to.</param>
			//void ReadShadowMap(GLTextureUnit textureUnit) const;

			/// <summary>
			/// Use directional light.
			/// </summary>
			/// <param name="locations">Directional light locations.</param>
			void UseLight(const DirectionalLightLocations& locations);
			~DirectionalLight();
		};
	}
}

#endif // !DIRECTIONAL_LIGHT_H