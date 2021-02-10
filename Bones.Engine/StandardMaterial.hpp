#pragma once

#ifndef STANDARD_MATERIAL_H

#define STANDARD_MATERIAL_H


#include <string>
#include "MaterialStructs.hpp"
#include "Texture2D.hpp"
#include "BaseMaterial.hpp"
#include "ShaderManager.hpp"
#include "StencilOutlineShader.hpp"

namespace Bones
{
	namespace Shaders
	{
		namespace Material
		{
			class MaterialShader;
		}
	}

	namespace Textures
	{
		class CubeTexture;
	}
}


using std::string;
using glm::vec4;
using Bones::Materials::BaseMaterial;
using Bones::Textures::CubeTexture;

using namespace Bones::Textures;

using  Bones::Shaders::Material::MaterialShader;
using  Bones::Shaders::Material::MaterialShaderOptions;

using Bones::Shaders::Stencil::StencilOutlineShader;

namespace Bones
{
	namespace Materials
	{
	

		typedef int polygon_mode;

		/// <summary>
		/// The standard material.
		/// </summary>
		class StandardMaterial final : public BaseMaterial
		{
		private:

			standard_material_options m_options;
			vec4 m_diffuseColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			polygon_mode m_polygonMode = GL_FILL;
			bool m_renderWireframe = false;



		public:

			MaterialShader* m_shader = nullptr;
			Texture2D* m_diffuseTexture = nullptr;
			Texture2D* m_specularTexture = nullptr;
			CubeTexture* m_reflectionTexture = nullptr;

			float m_specularIntensity = 1.0f, m_specularShininess = 10.0f;

			StandardMaterial(const string& name, standard_material_options opts);
			StandardMaterial(const string& name, StandardMaterialOptions opts);
			~StandardMaterial();

			/// <summary>
			/// Gets the polygon mode, which corresponds to GL_LINE or GL_FILL.
			/// </summary>
			inline const polygon_mode& GetPolygonMode() const noexcept { return m_polygonMode; }

			inline const bool& GetRenderWireframe() const noexcept { return m_renderWireframe; }
			void SetRenderWireframe(bool val)
			{
				m_renderWireframe = val;
				m_polygonMode = val ? GL_LINE : GL_FILL;
			}

			/// <summary>
			/// Gets the diffuse texture.
			/// </summary>
			/// <param name="m_diffuseTexture">The diffuse texture pointer. Can be null.</param>
			inline Texture2D* GetDiffuseTexture() const noexcept { return m_diffuseTexture; }

			/// <summary>
			/// Set the diffuse texture.
			/// </summary>
			/// <param name="diffuseTexture">The diffuse texture.</param>
			void SetDiffuseTexture(Texture2D* diffuseTexture);

			/// <summary>
			/// Gets the specular texture 
			/// </summary>
			inline Texture2D* GetSpeculartexture() const noexcept { return m_specularTexture; }

			/// <summary>
			/// Sets the specular texture.
			/// </summary>
			void SetSpecularTexture(Texture2D* specularTexture);

			/// <summary>
			/// Sets the reflection texture from paths.
			/// </summary>
			/// <param name="right"></param>
			/// <param name="left"></param>
			/// <param name="top"></param>
			/// <param name="bottom"></param>
			/// <param name="front"></param>
			/// <param name="back"></param>
			void SetReflectionTexture(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back);

			/// <summary>
			/// Sets the diffuse color.
			/// </summary>
			void SetDiffuseColor(vec4 color);

			/// <summary>
			/// Set the diffuse texture from path.
			/// </summary>
			/// <param name="diffuseTexturePath">The diffuse texture path.</param>
			void SetDiffuseTexture(const string& diffuseTexturePath);

			/// <summary>
			/// Set the specular texture from path.
			/// </summary>
			/// <param name="specularTexturePath">The specular texture</param>
			void SetSpecularTexture(const string& specularTexturePath);

			const float GetSpecularIntensity() const { return m_specularIntensity; }
			const float GetShininess() const { return m_specularShininess; }

			void UseMaterial() override;
		};
	}
}

#endif // !STANDARD_MATERIAL_H