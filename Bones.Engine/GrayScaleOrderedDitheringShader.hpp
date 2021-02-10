#pragma once 

#ifndef  GRAYSCALE_ORDERED_DITHERING_SHADER_H

#define  GRAYSCALE_ORDERED_DITHERING_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class GrayScaleOrderedDitheringShader final : public BasePostProcessShader
			{
			public:
				GrayScaleOrderedDitheringShader();
			};
		}
	}
}

#endif // ! GRAYSCALE_ORDERED_DITHERING_SHADER_H#pragma once
