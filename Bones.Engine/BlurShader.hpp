#pragma once 

#ifndef  BLUR_SHADER_H

#define  BLUR_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class BlurShader final : public BasePostProcessShader
			{
			public:
				BlurShader();
			};
		}
	}
}

#endif // ! BLUR_SHADER_H
