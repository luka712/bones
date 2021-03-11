#pragma once

#ifndef FRAMEBUFFER_MANAGER_H

#define FRAMEBUFFER_MANAGER_H

#include <vector>
#include <memory>
#include "utils.h"
#include "BasePostProcessShader.hpp"
#include "PostProcessFramebuffer.hpp"
#include "NightVisionPostProcessFramebuffer.hpp"

using std::vector;
using Bones::Framebuffers::PostProcess::PostProcessFramebuffer;
using Bones::Framebuffers::PostProcess::NightVisionPostProcessFramebuffer;
using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Managers
	{
		/// <summary>
		/// The class responsible for creation and control of lifetime of various framebuffers.
		/// </summary>
		class FramebufferManager final
		{

		public:
			Bones::State m_state = Bones::State::New;

			// contains all the post process framebuffers.
			static vector<std::unique_ptr<PostProcessFramebuffer>> m_postProcessFramebuffers;

			/// <summary>
			/// Load all the the created process framebuffers.
			/// </summary>
			void Load();

			/// <summary>
			/// Initialize all the created post process framebuffers.
			/// </summary>
			void Initialize();

			static PostProcessFramebuffer* GetOrCreateGrayScaleFramebuffer();
			static PostProcessFramebuffer* GetOrCreateInvertColorFramebuffer();
			static PostProcessFramebuffer* GetOrCreateSharpenFramebuffer();
			static PostProcessFramebuffer* GetOrCreateDetectEdgeFramebuffer();
			static PostProcessFramebuffer* GetOrCreateBlurFramebuffer();
			static PostProcessFramebuffer* GetOrCreateGrayScaleOrderedDitheringFramebuffer();
			static NightVisionPostProcessFramebuffer* GetOrCreateNightVisionFramebuffer();

			/// <summary>
			/// Delete this class. Releases and remove all the buffers.
			/// </summary>
			static void Delete();
		private:

			/// <summary>
			/// Gets or creates the post process framebuffer.
			/// </summary>
			template<typename TFramebuffer = PostProcessFramebuffer, typename TShader = BasePostProcessShader>
			static TFramebuffer* GetOrCreatePostProcessFramebuffer(TShader* ptr, const std::string& name)
			{
				for (size_t i = 0; i < m_postProcessFramebuffers.size(); i++)
				{
					PostProcessFramebuffer& fb = (*m_postProcessFramebuffers.at(i));

					if (typeid(fb.m_postProcessShader).name() == typeid(*ptr).name())
					{
						return static_cast<TFramebuffer*>(&fb);
					}
				}

				m_postProcessFramebuffers.emplace_back(new TFramebuffer(ptr));
				TFramebuffer* fb = static_cast<TFramebuffer*>(&(*m_postProcessFramebuffers.back()));
				Bones::Utils::GenerateName< PostProcessFramebuffer>(name, m_postProcessFramebuffers, *static_cast<PostProcessFramebuffer*>(fb));
				fb->Initialize();
				fb->Load();

				return fb;
			}
		};
	}
}

#endif // !FRAMEBUFFER_MANAGER_H
