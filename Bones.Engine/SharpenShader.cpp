#include "SharpenShader.hpp"
#include "Constants.hpp"
#include "ShaderParser.hpp"

using Bones::Shaders::PostProcess::SharpenShader;
using Bones::Loaders::ShaderParser;

SharpenShader::SharpenShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "Sharpen" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}
