#pragma once

#ifndef POSTPROCESS_FRAMEBUFFER_H

#define POSTPROCESS_FRAMEBUFFER_H

#include <vector>
#include <functional>
#include <unordered_map>
#include "BaseFramebuffer.hpp"
#include "core_types.h"

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
			class PostProcessFramebuffer : public BaseFramebuffer<PostProcessFramebuffer>
			{			
			public:

				enum class ValueType
				{
					TEXTURE,
					FLOAT,
					INT,
					VEC2,
					VEC3 
				};

				struct PostProcessFramebufferValue
				{
					ValueType m_type;
					I32 m_locationId;
					Bones::Variant m_value;
				};

				// GL Render Buffer Object. https://www.khronos.org/opengl/wiki/Renderbuffer_Object
				U32 m_renderBufferObject = 0;

				// texture id ( reference to texture to which effect is to be applied, usually texture which represents whatever 
				// is to be drawn to screen. 
				U32 m_textureId = 0;

				// Reference to shader. Stuff like blur shader, edge shader , night vision shader etc... 
				BasePostProcessShader* m_postProcessShader = nullptr;

				// All the value exposed by post process framebuffer
				std::unordered_map<std::string, PostProcessFramebufferValue> m_values;

				/// <summary>
				/// Constructor. Takes pointer to base post process shader.
				/// </summary>
				/// <param name="basePostProcessShader">basePostProcessShader</param>
				PostProcessFramebuffer(BasePostProcessShader* basePostProcessShader);

				~PostProcessFramebuffer();

				/// <summary>
				/// Preinitalize step. Implement is something is to be loaded before buffer is initialized.
				/// </summary>
				void Load_impl();

				/// <summary>
				/// Binds all the uniforms to shader.
				/// </summary>
				void BindUniforms_impl();

				/// <summary>
				/// Initialize. Create frame buffer, render buffer and texture.
				/// </summary>
				void Initialize_impl();

				/// <summary>
				/// Destroy the framebuffer and associated resources.
				/// </summary>
				void Destroy_impl();

				/// <summary>
				/// Render the actual framebuffer. This actually binds to framebuffer 0.
				/// </summary>
				void Render_impl();

				/// <summary>
				/// Renders the actual framebuffer. 
				/// </summary>
				/// <param name="renderBufferObject">To which render buffer object to render to. 0 is default.</param>
				void Render(U32 renderBufferObject);

			protected:
				// -- INTERNAL EVENTS
				std::function<void()> m_onLoad;
				std::function<void()> m_onInitialized;
				std::function<void()> m_onBindUniforms;

				/// <summary>
				/// Adds value to values
				/// </summary>
				/// <param name="prop">Name of property as defined in shader. Acts as key if keyName is not provided</param>
				/// <param name="val">Value</param>
				/// <param name="type">The type of value as defined in ValueType.</param>
				/// <param name="keyName">Name to refer to in property is to be fetched.</param>
				void AddValue(const std::string& prop, Bones::Variant val, ValueType type, const std::string& keyName = "");
			private:
				// The geometry for quad. Contains vertices for quad rendering ( screen ) 
				QuadScreenGeometry* m_quadScreenGeometry;
			};
		}
	}
}

#endif // !POSTPROCESS_FRAMEBUFFER_H