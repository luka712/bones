#include <typeinfo>
#include "FramebufferManager.hpp"
#include "PostProcessFramebuffer.hpp"
#include "GrayScaleShader.hpp"
#include "InvertColorShader.hpp"
#include "SharpenShader.hpp"
#include "DetectEdgeShader.hpp"
#include "BlurShader.hpp"
#include "GrayScaleOrderedDitheringShader.hpp"
#include "NightVisionShader.hpp"
#include "NightVisionPostProcessFramebuffer.hpp"
#include "ShaderManager.hpp"

using namespace Bones::Shaders::PostProcess;

using std::type_info;
using Bones::Managers::FramebufferManager;
using Bones::Managers::ShaderManager;
using Bones::Shaders::PostProcess::NightVisionShader;
using Bones::Framebuffers::PostProcess::NightVisionPostProcessFramebuffer;

// collection of post process framebuffers.
vector<std::unique_ptr<PostProcessFramebuffer>> FramebufferManager::m_postProcessFramebuffers;


void FramebufferManager::Load()
{
	m_state = Bones::State::Loaded;
	for (std::unique_ptr<PostProcessFramebuffer>& fb : m_postProcessFramebuffers)
	{
		fb->Load();
	}
}

void FramebufferManager::Initialize()
{
	m_state = Bones::State::Initialized;
	for (std::unique_ptr<PostProcessFramebuffer>& fb : m_postProcessFramebuffers)
	{
		fb->Initialize();
	}
}

PostProcessFramebuffer* FramebufferManager::GetOrCreateGrayScaleFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer(ShaderManager::GetOrCreateGrayScaleShader());
}

PostProcessFramebuffer* FramebufferManager::GetOrCreateInvertColorFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer(ShaderManager::GetOrCreateInvertColorShader());
}

PostProcessFramebuffer* FramebufferManager::GetOrCreateSharpenFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer(ShaderManager::GetOrCreateSharpenShader());
}

PostProcessFramebuffer* FramebufferManager::GetOrCreateDetectEdgeFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer(ShaderManager::GetOrCreateDetectEdgeShader());
}

PostProcessFramebuffer* FramebufferManager::GetOrCreateBlurFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer(ShaderManager::GetOrCreateBlurShader());
}

PostProcessFramebuffer* FramebufferManager::GetOrCreateGrayScaleOrderedDitheringFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer(ShaderManager::GetOrCreateGrayScaleOrderedDitheringShader());
}

NightVisionPostProcessFramebuffer* FramebufferManager::GetOrCreateNightVisionFramebuffer()
{
	return GetOrCreatePostProcessFramebuffer<NightVisionPostProcessFramebuffer, NightVisionShader>(ShaderManager::GetOrCreateNightVisionShader());
}

void FramebufferManager::Delete()
{
	m_postProcessFramebuffers.clear();
}

