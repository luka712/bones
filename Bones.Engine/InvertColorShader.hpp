#pragma once 

#ifndef  INVERT_COLOR_SHADER_H

#define  INVERT_COLOR_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class InvertColorShader final : public BasePostProcessShader
			{
			public:
				InvertColorShader();
			};
		}
	}
}

#endif // ! INVERT_COLOR_SHADER_H