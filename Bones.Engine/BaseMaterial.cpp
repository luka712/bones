#include "BaseMaterial.hpp"
#include "BaseShader.hpp"

using Bones::Materials::BaseMaterial;


BaseMaterial::BaseMaterial()
{
	m_shader = nullptr;
}

BaseMaterial::BaseMaterial(const string& name, BaseShader* shader)
	: m_name(name),m_shader(shader)
{
}


void BaseMaterial::Initialize()
{
	if (m_initialized) return;

	m_initialized = true;
	m_shader->Initialize();
}

void BaseMaterial::UseMaterial()
{
	for (size_t i = 0; i < m_textures.size(); i++)
	{
		m_textures[i]->BindTexture(static_cast<int>(i));
	}
}



void BaseMaterial::AddTexture(BaseTexture* tex)
{
	m_textures.push_back(tex);
	m_usedTextureUnits++;
}

BaseMaterial::~BaseMaterial()
{
	m_textures.clear();
}
