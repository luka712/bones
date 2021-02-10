#pragma once

#ifndef SHADER_MANAGER_H

#define SHADERMANAGER_H

#include "MaterialShaderStructs.hpp"
#include "BaseShader.hpp"
#include "SkyboxShader.hpp"
#include <string>
#include <map>

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class GrayScaleShader;
			class InvertColorShader;
			class SharpenShader;
			class BlurShader;
			class DetectEdgeShader;
			class GrayScaleOrderedDitheringShader;
			class NightVisionShader;
		}

		namespace Environment
		{
			class SkyboxShader;
		}

		namespace Stencil
		{
			class StencilOutlineShader;
		}

		namespace Material
		{
			class MaterialShader;
		}
	}
}

using Bones::Shaders::BaseShader;
using namespace Bones::Shaders::PostProcess;
using Bones::Shaders::Environment::SkyboxShader;
using Bones::Shaders::Stencil::StencilOutlineShader;
using Bones::Shaders::Material::MaterialShader;
using Bones::Shaders::Material::MaterialShaderOptions;
using std::map;
using std::string;

namespace Bones
{
	namespace Managers
	{
		/// <summary>
		/// The shader manager.
		/// </summary>
		class ShaderManager
		{
		private:
			static map<material_shader_options, MaterialShader*> m_materialShaderCache;
			static StencilOutlineShader* m_stencilOutlineShader;

			static GrayScaleShader* m_grayScaleShader;
			static InvertColorShader* m_invertColorShader;
			static SharpenShader* m_sharpenShader;
			static DetectEdgeShader* m_detectEdgeShader;
			static BlurShader* m_blurShader;
			static GrayScaleOrderedDitheringShader* m_grayScaleOrderedDitheringShader;
			static NightVisionShader* m_nightVisionShader;

			static SkyboxShader* m_skyboxShader;

			template <typename T = BaseShader> 
			static T* GetOrCreate(T* ptr);
			
		public:
			static MaterialShader* GetOrCreateMaterialShader(const MaterialShaderOptions& opts);
			static MaterialShader* GetOrCreateMaterialShader(const material_shader_options opts);
			
			static StencilOutlineShader* GetOrCreateStencilOutlineShader();

			// post process shaders
			static GrayScaleShader* GetOrCreateGrayScaleShader();
			static InvertColorShader* GetOrCreateInvertColorShader();
			static SharpenShader* GetOrCreateSharpenShader();
			static DetectEdgeShader* GetOrCreateDetectEdgeShader();
			static BlurShader* GetOrCreateBlurShader();
			static GrayScaleOrderedDitheringShader* GetOrCreateGrayScaleOrderedDitheringShader();
			static NightVisionShader* GetOrCreateNightVisionShader();

			static SkyboxShader* GetOrCreateSkyboxShader();

			static void Delete();
		};
	}
}

#endif // !SHADER_MANAGER_H