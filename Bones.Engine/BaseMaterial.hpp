#pragma once

#ifndef BASE_MATERIAL_H

#define BASE_MATERIAL_H

#include <vector>
#include <string>
#include "BaseTexture.hpp"

namespace Bones
{
	namespace Shaders
	{
		class BaseShader;
	}
}

using std::vector;
using std::string;

using Bones::Shaders::BaseShader;
using namespace Bones::Textures;

namespace Bones
{
	namespace Materials
	{
		class BaseMaterial
		{
		protected:			
			string m_name;
			bool m_initialized = false;
			size_t m_usedTextureUnits;
			unsigned int m_reservedMaterialTextures;
			BaseShader* m_shader;
			vector<BaseTexture*> m_textures;

			BaseMaterial();

			/// <summary>
			/// Adds the texture to list of textures.
			/// </summary>
			/// <param name="tex">Texture to add.</param>
			void AddTexture(BaseTexture* tex);

		public:
			BaseMaterial(const string& name, BaseShader* shader);

#pragma region Getters 

			const string& GetName() const noexcept { return m_name; }

			/// <summary>
			/// Gets all the textures.
			/// </summary>
			/// <returns></returns>
			const vector<BaseTexture*>& GetTextures() const { return m_textures; }

			/// <summary>
			/// Gets the number of used texture units.
			/// </summary>
			/// <returns>Number of used texture units.</returns>
			const size_t GetNumOfUsedTextureUnits() const noexcept { return m_usedTextureUnits; }

			/// <summary>
			/// Gets the number of textures reserved for material.
			/// For example if material is using diffuse and normal, this should return 2.
			/// </summary>
			/// <returns>Number of reserver material textures.</returns>
			const unsigned int GetNumOfReservedMaterialTextures() const noexcept { return m_reservedMaterialTextures; }

			template<typename TShader = BaseShader>
			TShader& GetShader() const { return *m_shader; }

#pragma endregion

			// methods
			void Initialize();

			virtual void UseMaterial();

			virtual ~BaseMaterial();
		};
	}
}

#endif // !BASE_MATERIAL_H