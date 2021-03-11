#pragma once

#ifndef POST_PROCESSS_PIPELINE_H

#define POST_PROCESSS_PIPELINE_H

#include <vector>

using std::vector;

namespace Bones
{
	namespace Framebuffers
	{
		namespace PostProcess
		{
			class PostProcessFramebuffer;
			class NightVisionPostProcessFramebuffer;
		}
	}
}

using Bones::Framebuffers::PostProcess::PostProcessFramebuffer;
using Bones::Framebuffers::PostProcess::NightVisionPostProcessFramebuffer;

namespace Bones
{
	namespace PostProcessPipeline
	{
		class BasePostProcessPipeline
		{
		public:
			vector<PostProcessFramebuffer*> m_postProcessFramebuffers;

			~BasePostProcessPipeline();

			PostProcessFramebuffer* AddGrayScaleEffect();
			PostProcessFramebuffer* AddInvertColorEffect();
			PostProcessFramebuffer* AddSharpenEffect();
			PostProcessFramebuffer* AddDetectEdgeEffect();
			PostProcessFramebuffer* AddBlurEffect();
			PostProcessFramebuffer* AddGrayScaleOrderedDitheringEffect();
			NightVisionPostProcessFramebuffer* AddNightVisionEffect();

			void Bind() const;
			void Draw() const;
		private:
			void AddEffectToArray(PostProcessFramebuffer* ptr);

		};
	}
}

#endif // !POST_PROCESSS_PIPELINE_H