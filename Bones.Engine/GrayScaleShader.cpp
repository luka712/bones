#include "GrayScaleShader.hpp"
#include "Constants.hpp"
#include "ShaderParser.hpp"

using Bones::Shaders::PostProcess::GrayScaleShader;
using Bones::Loaders::ShaderParser;

GrayScaleShader::GrayScaleShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "GrayScale" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}
