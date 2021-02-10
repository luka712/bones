#include "DetectEdgeShader.hpp"
#include "Constants.hpp"
#include "ShaderParser.hpp"

using Bones::Shaders::PostProcess::DetectEdgeShader;
using Bones::Loaders::ShaderParser;

DetectEdgeShader::DetectEdgeShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "DetectEdge" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}
