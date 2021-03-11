#pragma once 

#ifndef  BASE_POST_PROCESS_SHADER_H

#define  BASE_POST_PROCESS_SHADER_H

#include <string>
#include "core_types.h"
#include "BaseShader.hpp"


using Bones::Shaders::BaseShader;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class BasePostProcessShader : public BaseShader
			{
			public:
				I32 m_textureLocation = 0;

				BasePostProcessShader();
				BasePostProcessShader(const std::string& vertexSource, const std::string& fragmentSource);

				void Initialize() override;
			};
		}
	}
}

#endif // ! BASE_POST_PROCESS_SHADER_H