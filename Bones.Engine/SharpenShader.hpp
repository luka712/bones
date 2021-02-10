#pragma once 

#ifndef  SHARPEN_SHADER_H

#define  SHARPEN_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class SharpenShader final : public BasePostProcessShader
			{
			public:
				SharpenShader();
			};
		}
	}
}

#endif // ! SHARPEN_SHADER_H