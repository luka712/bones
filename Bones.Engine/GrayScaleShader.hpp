#pragma once 

#ifndef  GRAYSCALE_SHADER_H

#define  GRAYSCALE_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class GrayScaleShader final : public BasePostProcessShader
			{
			public:
				GrayScaleShader();
			};
		}
	}
}

#endif // ! GRAYSCALE_SHADER_H