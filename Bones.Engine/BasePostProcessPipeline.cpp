#include "BasePostProcessPipeline.hpp"
#include "PostProcessFramebuffer.hpp"
#include "FramebufferManager.hpp"
#include "core_types.h"

using Bones::PostProcessPipeline::BasePostProcessPipeline;
using Bones::Managers::FramebufferManager;

BasePostProcessPipeline::~BasePostProcessPipeline()
{
	m_postProcessFramebuffers.clear();
}


void BasePostProcessPipeline::AddEffectToArray(PostProcessFramebuffer* ptr)
{
	bool hasOne = false;
	for (size_t i = 0; i < m_postProcessFramebuffers.size(); i++)
	{
		if (m_postProcessFramebuffers.at(i) == ptr)
		{
			hasOne = true;
		}
	}

	if (!hasOne)
	{
		m_postProcessFramebuffers.push_back(ptr);
	}
#if DEBUG
	if (hasOne)
	{
		LOG("Attempting to add grayscale shader. Shader was already added.");
	}
#endif
}


PostProcessFramebuffer* BasePostProcessPipeline::AddGrayScaleEffect()
{
	PostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateGrayScaleFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

PostProcessFramebuffer* BasePostProcessPipeline::AddInvertColorEffect()
{
	PostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateInvertColorFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

PostProcessFramebuffer* BasePostProcessPipeline::AddSharpenEffect()
{
	PostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateSharpenFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

PostProcessFramebuffer* BasePostProcessPipeline::AddDetectEdgeEffect()
{
	PostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateDetectEdgeFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

PostProcessFramebuffer* BasePostProcessPipeline::AddBlurEffect()
{
	PostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateBlurFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

PostProcessFramebuffer* BasePostProcessPipeline::AddGrayScaleOrderedDitheringEffect()
{
	PostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateGrayScaleOrderedDitheringFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

NightVisionPostProcessFramebuffer* BasePostProcessPipeline::AddNightVisionEffect()
{
	NightVisionPostProcessFramebuffer* ptr = FramebufferManager::GetOrCreateNightVisionFramebuffer();
	AddEffectToArray(ptr);
	return ptr;
}

void BasePostProcessPipeline::Bind() const
{
	if (m_postProcessFramebuffers.size() > 0)
	{
		m_postProcessFramebuffers.at(0)->Bind();
	}
}

void BasePostProcessPipeline::Draw() const
{
	if (m_postProcessFramebuffers.size() > 0)
	{
		if (m_postProcessFramebuffers.size() > 1)
		{
			m_postProcessFramebuffers.at(1)->Bind();
		}

		//m_postProcessFramebuffers.at(0)->Draw(m_postProcessFramebuffers.at(1)->m_renderBufferObject);
		m_postProcessFramebuffers.at(0)->Draw();

		for (size_t i = 1; i < m_postProcessFramebuffers.size(); i++)
		{
			PostProcessFramebuffer& fb = *m_postProcessFramebuffers.at(i);

			fb.Draw();
		}
	}
}



#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;


EMSCRIPTEN_BINDINGS(BasePostProcessPipeline_JS)
{
	class_<BasePostProcessPipeline>("BasePostProcessPipeline")
		.function("AddGrayScaleEffect", &BasePostProcessPipeline::AddGrayScaleEffect, emscripten::allow_raw_pointers())
		.function("AddInvertColorEffect", &BasePostProcessPipeline::AddInvertColorEffect, emscripten::allow_raw_pointers())
		.function("AddSharpenEffect", &BasePostProcessPipeline::AddSharpenEffect, emscripten::allow_raw_pointers())
		.function("AddDetectEdgeEffect", &BasePostProcessPipeline::AddDetectEdgeEffect, emscripten::allow_raw_pointers())
		.function("AddBlurEffect", &BasePostProcessPipeline::AddBlurEffect, emscripten::allow_raw_pointers())
		.function("AddGrayScaleOrderedDitheringEffect", &BasePostProcessPipeline::AddGrayScaleOrderedDitheringEffect, emscripten::allow_raw_pointers())
		.function("AddNightVisionEffect", &BasePostProcessPipeline::AddNightVisionEffect, emscripten::allow_raw_pointers());
}

#endif