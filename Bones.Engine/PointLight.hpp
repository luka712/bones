#pragma once
#include "BaseLight.hpp"
#include "OmniDirectionalLightShadowMap.hpp"
#include "MaterialShader.hpp"

namespace Bones 
{
	namespace Shaders 
	{
		namespace Material 
		{
			struct PointLightLocations;
		}
	}
}

using Bones::Shaders::Material::PointLightLocations;
//using namespace Bones::Shader;
using namespace Bones::Light;
//using namespace Bones::Shadow;

using glm::vec4;

namespace Bones
{
	namespace Light
	{
		class PointLight : public BaseLight
		{
		private:
			void RefreshShadowProjectionMatrices() noexcept;
		protected:
			vec3 m_position;
			ShadowSize m_shadowSize;
			float m_constant, m_linear, m_quadtratic;
			// TODO: replace by general omni directional light.
			//OmniDirectionalLightShadowMap* m_shadowMap;

			mat4 m_projection, m_view[6], m_projectionView[6];
			ProjectionNearFarPlane m_projectionPlane;

		public:
			vec3 m_specularColor = vec3(1, 1, 1);

			PointLight();
			PointLight(vec3 position);
			PointLight(vec3 position, vec3 color);
			PointLight(vec3 color, vec3 position, float exponent, float linear, float constant, ShadowSize shadowSize, ProjectionNearFarPlane projectionPlane);

			void Initialize() override;

			/// <summary>
			/// Gets the shadow map.
			/// </summary>
			/// <returns>The shadow map.</returns>
			//OmniDirectionalLightShadowMap* GetShadowMap() const noexcept { return m_shadowMap; }

			/// <summary>
			/// Gets the view matrices to be used for shadow rendering.
			/// </summary>
			/// <returns></returns>
			const mat4* GetLightProjectionViewMatrices() const noexcept { return m_projectionView; }

			/// <summary>
			/// Get the light position.
			/// </summary>
			/// <returns>Gets light position as vec3 reference.</returns>
			vec3& GetPosition() noexcept { return m_position; }

			/// <summary>
			/// Gets the far plane value.
			/// </summary>
			/// <returns>Far plane as float.</returns>
			const float GetFarPlane() const noexcept { return m_projectionPlane.farPlane; }

			/// <summary>
			/// Offset from GL_TEXTURE0 for n places
			/// </summary>
			/// <param name="textureUnit">The texture unit. For example GL_TEXTURE0</param>
			/// <param name="offset">N places to offset from. For example 1 results in GL_TEXTURE0 + 1 ... GL_TEXTURE1.</param>
			//void ReadShadowMap(GLTextureUnit textureUnit, unsigned int offset) const;

			/// <summary>
			/// For example GL_TEXTURE0.
			/// </summary>
			/// <param name="textureUnit">The texture unit.</param>
			/// <param name="offset">N places to offset from. For example 1 results in GL_TEXTURE0 + 1 ... GL_TEXTURE1.</param>
			//void ReadShadowMap(GLenum textureUnit, unsigned int offset) const;

			/// <summary>
			/// Use light
			/// </summary>
			/// <param name="pointLightLocations">Point light locations.</param>
			void UseLight(const PointLightLocations& pointLightLocations);


			void SetPosition(float x, float y, float z);
			void SetAttenuation(float constant, float linear, float exponent);
		};
	}
}