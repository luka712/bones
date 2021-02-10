#pragma once 

#ifndef OPENGL_ES_3_0_RENDERER_H

#define OPENGL_ES_3_0_RENDERER_H

#include "BaseRenderer.hpp"

using namespace Bones::Renderer;

namespace Bones
{
	namespace Renderer
	{
		class OpenGL_ES_3_0_Renderer final : public BaseRenderer
		{
		protected:
			int MajorVersion() const
			{
				return 3;
			}

			int MinorVersion() const
			{
				return 0;
			}

			void CreateWindowAndRenderer() override;
		};
	}

}

#endif //  OPENGL_ES_3_0_RENDERER_H



