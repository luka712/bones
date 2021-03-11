#pragma once

#ifndef BASEFRAMEBUFFER_H

#define BASEFRAMEBUFFER_H

#include "core_types.h"
#include "sdl_include.h"

namespace Bones
{
	namespace Framebuffers
	{
		/// <summary>
		/// The base abstract framebuffer class. 
		/// Any framebuffer to be created for various stuff, such as postprocess is to inherit from this class.
		/// </summary>
		template<typename T>
		class BaseFramebuffer : public ILifeCycle<T>
		{
		public:
			// GLFramebuffer id as link to OpenGL.
			U32 m_fbo = 0;

			~BaseFramebuffer()
			{
				LOG_DESTRUCTOR();
				DeleteFramebuffer();
			}

			/// <summary>
			/// Binds the framebuffer so that it can be drawn to.
			/// </summary>
			void Bind() const
			{
				glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
			}


			/// <summary>
			/// Sends uniforms to GPU.
			/// </summary>
			void BindUniforms()
			{
				static_cast<T*>(this)->BindUniforms_impl();
			}

			/// <summary>
			/// Unbinds the framebuffer.
			/// </summary>
			void Unbind() const
			{
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			/// <summary>
			/// Delete the Framebuffer in GPU.
			/// </summary>
			void DeleteFramebuffer()
			{
				glDeleteBuffers(1, &m_fbo);
			}
		};
	}
}

#endif // !BASEFRAMEBUFFER_H

