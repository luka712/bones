#include "InvertColorShader.hpp"
#include "Constants.hpp"
#include "ShaderParser.hpp"

using Bones::Shaders::PostProcess::InvertColorShader;
using Bones::Loaders::ShaderParser;

InvertColorShader::InvertColorShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "InvertColor" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}
