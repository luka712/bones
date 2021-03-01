#pragma once

#ifndef BASEFRAMEBUFFER_H

#define BASEFRAMEBUFFER_H

#include "core_types.h"
#include "core_types.h"

namespace Bones
{
	namespace Framebuffers
	{
		/// <summary>
		/// The base abstract framebuffer class. 
		/// Any framebuffer to be created for various stuff, such as postprocess is to inherit from this class.
		/// </summary>
		class BaseFramebuffer
		{
		protected:
			// GLFramebuffer id.
			unsigned int m_fbo = 0;

			BaseFramebuffer& operator=(const BaseFramebuffer&) = delete;
		public:
			// The state
			Bones::State m_state = Bones::State::New;
			~BaseFramebuffer();

			/// <summary>
			/// The load. First method to be called after creation of instance.
			/// </summary>
			virtual void Load() = 0;
			/// <summary>
			/// The initialize. Called after Load. Creation of GLFramebuffer
			/// alongside other GL/Vulkan/WebGPU stuff should be done in this method
			/// </summary>
			virtual void Initialize() = 0;

			/// <summary>
			/// Binds the framebuffer so that it can be drawn to.
			/// </summary>
			void Bind() const;

			/// <summary>
			/// Unbinds the framebuffer.
			/// </summary>
			void Unbind() const;

			/// <summary>
			/// Destroy the framebuffer and associated resources.
			/// </summary>
			virtual void Destroy() = 0;  
		};
	}
}

#endif // !BASEFRAMEBUFFER_H

