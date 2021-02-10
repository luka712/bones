#pragma once 

#ifndef  DETECT_EDGE_SHADER_H

#define  DETECT_EDGE_SHADER_H

#include "BasePostProcessShader.hpp"

using Bones::Shaders::PostProcess::BasePostProcessShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class DetectEdgeShader final : public BasePostProcessShader
			{
			public:
				DetectEdgeShader();
			};
		}
	}
}

#endif // ! DETECT_EDGE_SHADER_H
