#include "GrayScaleOrderedDitheringShader.hpp"
#include "core_types.h"
#include "ShaderParser.hpp"

using Bones::Shaders::PostProcess::GrayScaleOrderedDitheringShader;
using Bones::Loaders::ShaderParser;

GrayScaleOrderedDitheringShader::GrayScaleOrderedDitheringShader()
{
	string path = string(POSTPROCESS_SHADERS_PATH) + "GrayScaleOrderedDithering" + SHADER_SUFFIX;
	ShaderParser parser;
	ShaderSourceData data = parser.LoadFromFile(path);
	m_vertexSource = data.vertexSource;
	m_fragmentSource = data.fragmentSource;
}
