#include "Constants.hpp"
#include "ShaderManager.hpp"
#include "GrayScaleShader.hpp"
#include "SharpenShader.hpp"
#include "InvertColorShader.hpp"
#include "StencilOutlineShader.hpp"
#include "DetectEdgeShader.hpp"
#include "BlurShader.hpp"
#include "GrayScaleOrderedDitheringShader.hpp"
#include "NightVisionShader.hpp"
#include "MaterialShader.hpp"
#include "SkyboxShader.hpp"

using Bones::Managers::ShaderManager;

map<material_shader_options, MaterialShader*> ShaderManager::m_materialShaderCache = map<material_shader_options, MaterialShader*>();
StencilOutlineShader* ShaderManager::m_stencilOutlineShader = nullptr;

GrayScaleShader* ShaderManager::m_grayScaleShader = nullptr;
InvertColorShader* ShaderManager::m_invertColorShader = nullptr;
SharpenShader* ShaderManager::m_sharpenShader = nullptr;
DetectEdgeShader* ShaderManager::m_detectEdgeShader = nullptr;
BlurShader* ShaderManager::m_blurShader = nullptr;
GrayScaleOrderedDitheringShader* ShaderManager::m_grayScaleOrderedDitheringShader = nullptr;
NightVisionShader* ShaderManager::m_nightVisionShader = nullptr;

SkyboxShader* ShaderManager::m_skyboxShader = nullptr;


MaterialShader* ShaderManager::GetOrCreateMaterialShader(const MaterialShaderOptions& opts)
{
	return GetOrCreateMaterialShader(opts.ConvertToUL());
}

MaterialShader* ShaderManager::GetOrCreateMaterialShader(const material_shader_options opts)
{
	// if exists just return.
	map<unsigned long, MaterialShader*>::iterator entry = ShaderManager::m_materialShaderCache.find(opts);
	if (entry != ShaderManager::m_materialShaderCache.end())
	{
		return entry->second;
	}
	else
	{
		// create shader.
		MaterialShader* ptr = new MaterialShader(opts);
		ShaderManager::m_materialShaderCache.emplace(opts, ptr);
		ptr->Initialize();
		return ptr;
	}
}

StencilOutlineShader* ShaderManager::GetOrCreateStencilOutlineShader()
{
	if (ShaderManager::m_stencilOutlineShader == nullptr)
	{
		ShaderManager::m_stencilOutlineShader = new StencilOutlineShader();
		ShaderManager::m_stencilOutlineShader->Initialize();
	}
	return ShaderManager::m_stencilOutlineShader;
}

GrayScaleShader* ShaderManager::GetOrCreateGrayScaleShader()
{
	if (ShaderManager::m_grayScaleShader == nullptr)
	{
		ShaderManager::m_grayScaleShader = new GrayScaleShader();
		ShaderManager::m_grayScaleShader->Initialize();
	}
	return ShaderManager::m_grayScaleShader;
}

InvertColorShader* ShaderManager::GetOrCreateInvertColorShader()
{
	if (ShaderManager::m_invertColorShader == nullptr)
	{
		ShaderManager::m_invertColorShader = new InvertColorShader();
		ShaderManager::m_invertColorShader->Initialize();
	}
	return ShaderManager::m_invertColorShader;
}

SharpenShader* ShaderManager::GetOrCreateSharpenShader()
{
	if (ShaderManager::m_sharpenShader == nullptr)
	{
		ShaderManager::m_sharpenShader = new SharpenShader();
		ShaderManager::m_sharpenShader->Initialize();
	}
	return ShaderManager::m_sharpenShader;
}

DetectEdgeShader* ShaderManager::GetOrCreateDetectEdgeShader()
{
	if (ShaderManager::m_detectEdgeShader == nullptr)
	{
		ShaderManager::m_detectEdgeShader = new DetectEdgeShader();
		ShaderManager::m_detectEdgeShader->Initialize();
	}
	return ShaderManager::m_detectEdgeShader;
}

BlurShader* ShaderManager::GetOrCreateBlurShader()
{
	if (ShaderManager::m_blurShader == nullptr)
	{
		ShaderManager::m_blurShader = new BlurShader();
		ShaderManager::m_blurShader->Initialize();
	}
	return ShaderManager::m_blurShader;
}

GrayScaleOrderedDitheringShader* ShaderManager::GetOrCreateGrayScaleOrderedDitheringShader()
{
	if (ShaderManager::m_grayScaleOrderedDitheringShader == nullptr)
	{
		ShaderManager::m_grayScaleOrderedDitheringShader = new GrayScaleOrderedDitheringShader();
		ShaderManager::m_grayScaleOrderedDitheringShader->Initialize();
	}
	return ShaderManager::m_grayScaleOrderedDitheringShader;
}

NightVisionShader* Bones::Managers::ShaderManager::GetOrCreateNightVisionShader()
{
	if (m_nightVisionShader == nullptr)
	{
		m_nightVisionShader = new NightVisionShader();
		m_nightVisionShader->Initialize();
	}

	return m_nightVisionShader;
}

SkyboxShader* ShaderManager::GetOrCreateSkyboxShader()
{
	if (ShaderManager::m_skyboxShader == nullptr)
	{
		ShaderManager::m_skyboxShader = new SkyboxShader();
		ShaderManager::m_skyboxShader->Initialize();
	}
	return ShaderManager::m_skyboxShader;
}

void ShaderManager::Delete()
{
	for (map<unsigned long, MaterialShader*>::iterator it = ShaderManager::m_materialShaderCache.begin();
		it != ShaderManager::m_materialShaderCache.end(); ++it)
	{
		delete it->second;
	}
	ShaderManager::m_materialShaderCache.clear();

	DELETE_PTR(ShaderManager::m_stencilOutlineShader);

	// post process
	DELETE_PTR(ShaderManager::m_grayScaleShader);
	DELETE_PTR(ShaderManager::m_invertColorShader);
	DELETE_PTR(ShaderManager::m_sharpenShader);
	DELETE_PTR(ShaderManager::m_detectEdgeShader);
	DELETE_PTR(ShaderManager::m_blurShader);
	DELETE_PTR(ShaderManager::m_grayScaleOrderedDitheringShader);
	DELETE_PTR(m_nightVisionShader);

	DELETE_PTR(ShaderManager::m_skyboxShader);
}
