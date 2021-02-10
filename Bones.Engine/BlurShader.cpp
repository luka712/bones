#include "BlurShader.hpp"
#include "Constants.hpp"
#include "ShaderParser.hpp"

using Bones::Shaders::PostProcess::BlurShader;
using Bones::Loaders::ShaderParser;

BlurShader::BlurShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "Blur" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}
