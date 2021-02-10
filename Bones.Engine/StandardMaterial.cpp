#include "StandardMaterial.hpp"
#include "MaterialShader.hpp"
#include "TextureManager.hpp"
#include "MaterialShaderStructs.hpp"
#include "CubeTexture.hpp"

using Bones::Materials::StandardMaterial;
using Bones::Managers::ShaderManager;
using Bones::Managers::TextureManager;
using Bones::Shaders::Material::MaterialShader;
using Bones::Shaders::Material::MaterialLocations;


StandardMaterial::StandardMaterial(const string& name, StandardMaterialOptions opts)
	: StandardMaterial(name, opts.ConvertToUL())
{


}


StandardMaterial::StandardMaterial(const string& name, standard_material_options opts)
{
	m_options = opts;
	m_name = name;
	m_shader = ShaderManager::GetOrCreateMaterialShader(opts);
	BaseMaterial::m_shader = static_cast<BaseShader*>(m_shader);
	m_reservedMaterialTextures = 1;
}



void StandardMaterial::SetDiffuseTexture(Texture2D* diffuseTexture)
{
	if (m_diffuseTexture)
	{
		m_diffuseTexture = nullptr;
		m_usedTextureUnits--;
	}

	if (diffuseTexture)
	{
		m_diffuseTexture = diffuseTexture;
		m_usedTextureUnits++;
		m_options |= STANDARD_MATERIAL_USE_DIFFUSE_MAP;
		m_shader = ShaderManager::GetOrCreateMaterialShader(m_options);
	}
}


void StandardMaterial::SetSpecularTexture(Texture2D* specularTexture)
{
	if (m_specularTexture)
	{
		delete m_specularTexture;
		m_specularTexture = nullptr;
		m_usedTextureUnits--;
	}

	if (specularTexture)
	{
		m_specularTexture = specularTexture;
		m_usedTextureUnits++;
		m_options |= STANDARD_MATERIAL_USE_SPECULAR_MAP;
		m_shader = ShaderManager::GetOrCreateMaterialShader(m_options);
	}
}

void StandardMaterial::SetDiffuseColor(vec4 color)
{
	m_diffuseColor = color;
}

void StandardMaterial::SetDiffuseTexture(const string& diffuseTexturePath)
{
	SetDiffuseTexture(TextureManager::GetOrCreateTexture2D(diffuseTexturePath));
}

void StandardMaterial::SetSpecularTexture(const string& specularTexturePath)
{
	SetSpecularTexture(TextureManager::GetOrCreateTexture2D(specularTexturePath));
}

void StandardMaterial::SetReflectionTexture(const string& right, const string& left, const string& top, const string& bottom, const string& front, const string& back)
{
	m_reflectionTexture = TextureManager::GetOrCreateCubeTexture(right, left, top, bottom, front, back);
}

void StandardMaterial::UseMaterial()
{
	MaterialLocations& materialLocations = m_shader->m_materialLocations;

	int textureUnitOffset = 0;
	int cubeTextureUnitOffset = 0;

	// 2d textures
	if (m_diffuseTexture)
	{
		m_shader->SetInt(materialLocations.diffuseMapLocation, textureUnitOffset);
		m_diffuseTexture->BindTexture(textureUnitOffset);
		textureUnitOffset++;
	}
	if (m_specularTexture)
	{
		m_shader->SetInt(materialLocations.specularMapLocation, textureUnitOffset);
		m_specularTexture->BindTexture(textureUnitOffset);
		textureUnitOffset++;
	}

	// cube textures
	if (m_reflectionTexture)
	{
		m_shader->SetInt(materialLocations.reflectionMapLocation, cubeTextureUnitOffset);
		m_reflectionTexture->BindTexture(cubeTextureUnitOffset);
		cubeTextureUnitOffset++;
	}

	m_shader->SetFloat4(materialLocations.diffuseColorLocation, m_diffuseColor);
	m_shader->SetFloat(materialLocations.specularShininessLocation, m_specularShininess);
}


StandardMaterial::~StandardMaterial()
{
	m_shader = nullptr;

	BaseMaterial::~BaseMaterial();
	
	m_diffuseTexture = nullptr;
	m_specularTexture = nullptr;
	m_specularTexture = nullptr;
	
	m_usedTextureUnits = 0;
}

