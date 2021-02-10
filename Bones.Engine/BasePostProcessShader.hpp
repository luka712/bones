#pragma once 

#ifndef  BASE_POST_PROCESS_SHADER_H

#define  BASE_POST_PROCESS_SHADER_H

#include <string>
#include "BaseShader.hpp"


using Bones::Shaders::BaseShader;
using std::string;

namespace Bones
{
	namespace Shaders
	{
		namespace PostProcess
		{
			class BasePostProcessShader : public BaseShader
			{
			public:
				int m_textureLocation = 0;
				BasePostProcessShader();
				BasePostProcessShader(string vertexSource, string fragmentSource);

				void Initialize() override;
			};
		}
	}
}

#endif // ! BASE_POST_PROCESS_SHADER_H