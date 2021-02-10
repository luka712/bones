#pragma once

#include "BaseFramebuffer.hpp"

#ifndef POSTPROCESS_FRAMEBUFFER_H

#define POSTPROCESS_FRAMEBUFFER_H

#include "Constants.hpp"

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class BasePostProcessShader;
		}
	}

	namespace Geometry
	{
		class QuadScreenGeometry;
	}
}

using Bones::Shaders::PostProcess::BasePostProcessShader;
using Bones::Geometry::QuadScreenGeometry;
using Bones::Framebuffers::BaseFramebuffer;

namespace Bones
{
	namespace Framebuffers
	{
		namespace PostProcess
		{

			/// <summary>
			/// Post process framebuffer. 
			/// Represents framebuffer which is to be used when creating various post processing effects.
			/// </summary>
			class PostProcessFramebuffer : public BaseFramebuffer
			{
			private:
				// id generator. To be increased on creation of new instance.
				static unsigned int m_genId;

				// the id, texture id ( reference to texture to which effect is to be applied, usually texture which represents whatever 
				// is to be drawn to screen. 
				unsigned int m_id = 0,m_textureId = 0;

				// The geometry for quad. Contains vertices for quad rendering ( screen ) 
				QuadScreenGeometry* m_quadScreenGeometry;

				
			public:
				// GL Render Buffer Object. https://www.khronos.org/opengl/wiki/Renderbuffer_Object
				unsigned int m_renderBufferObject = 0;

				// Reference to shader. Stuff like blur shader, edge shader , night vision shader etc... 
				BasePostProcessShader* m_postProcessShader;

				/// <summary>
				/// Constructor. Takes pointer to base post process shader.
				/// </summary>
				/// <param name="basePostProcessShader">basePostProcessShader</param>
				PostProcessFramebuffer(BasePostProcessShader* basePostProcessShader);

				~PostProcessFramebuffer();


				/// <summary>
				/// Preinitalize step. Implement is something is to be loaded before buffer is initialized.
				/// </summary>
				void Load() override;

				/// <summary>
				/// Initialize. Create frame buffer, render buffer and texture.
				/// </summary>
				void Initialize() override;

				/// <summary>
				/// Destroy the framebuffer and associated resources.
				/// </summary>
				void Destroy() override;

				/// <summary>
				/// Sends uniforms to GPU.
				/// </summary>
				virtual void BindUniforms();

				/// <summary>
				/// Draws the actual framebuffer. This actually binds to framebuffer 0.
				/// </summary>
				virtual void Draw();

				/// <summary>
				/// Binds the framebuffer.
				/// </summary>
				/// <param name="renderBufferObject"></param>
				virtual void Draw(unsigned int renderBufferObject);
			};
		}
	}
}

#endif // !POSTPROCESS_FRAMEBUFFER_H