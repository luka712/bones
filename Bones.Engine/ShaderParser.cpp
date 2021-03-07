#include "ShaderParser.hpp"
#include "emscripten_include.h"

using namespace Bones::Loaders;

ShaderSourceData ShaderParser::ParseFromString(string& text) const
{
    string vertexSrc, geometrySrc, fragmentSrc;

    size_t vertexStart = text.find(m_vertexShaderVar);
    size_t geometryStart = text.find(m_geometryShaderVar);
    size_t fragmentStart = text.find(m_fragmentShaderVar);

    bool hasVertex = vertexStart != string::npos;
    bool hasGeometry = geometryStart != string::npos;
    bool hasFragment = fragmentStart != string::npos;

    if (hasVertex)
    {
        // support for geometry as well, if found, use it.
        size_t vertexEnd = fragmentStart - m_vertexShaderVar.size();
        if (hasGeometry)
        {
            vertexEnd = geometryStart - m_vertexShaderVar.size();
        }

        string vertexSource = text.substr(vertexStart + m_vertexShaderVar.size(), vertexEnd);

        // delete lines so that version is first thing in shader, if it's actually in shader.
        vertexStart = vertexSource.find(m_versionVar);
        if (vertexStart != string::npos)
        {
            vertexSrc = vertexSource.substr(vertexStart);
        }
    }

    if (hasGeometry)
    {
        size_t geometryEnd = fragmentStart - m_geometryShaderVar.size() - vertexSrc.size() - 1 - m_vertexShaderVar.size();

        string geometrySource = text.substr(geometryStart + m_geometryShaderVar.size(), geometryEnd);

        geometryStart = geometrySource.find(m_versionVar);
        if (geometryStart != string::npos)
        {
            geometrySrc = geometrySource.substr(geometryStart);
        }
    }


    if (hasFragment)
    {
        string fragmentSource = text.substr(fragmentStart + m_fragmentShaderVar.size());

        // same delete for fragment
        fragmentStart = fragmentSource.find(m_versionVar);
        if (fragmentStart != string::npos)
        {
            fragmentSrc = fragmentSource.substr(fragmentStart);
        }
    }


    return { vertexSrc, geometrySrc, fragmentSrc };
}

ShaderSourceData ShaderParser::LoadFromFile(const string& filepath) const
{
    FileLoader loader;
    string source = loader.ReadFileToString(filepath);
    return ParseFromString(source);
}

ShaderSourceData ShaderParser::ParseFromString(string& text, map<string, int> shaderReplace) const
{
    for (map<string, int>::iterator it = shaderReplace.begin(); it != shaderReplace.end(); ++it)
    {
        string replaceString = it->first;
        size_t position = text.find(replaceString, 0);
        string replacement = to_string(it->second);
        text.replace(position, replaceString.size(), replacement);
    }

    return ParseFromString(text);
}

ShaderSourceData ShaderParser::LoadFromFile(const string& filepath, map<string, int> shaderReplace) const
{
    FileLoader loader;
    string source = loader.ReadFileToString(filepath);
    return ParseFromString(source, shaderReplace);
}

#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;

EMSCRIPTEN_BINDINGS(ShaderParser)
{
    value_object<ShaderSourceData>("ShaderSourceData")
        .field("vertexSource", &ShaderSourceData::vertexSource)
        .field("fragmentSource", &ShaderSourceData::fragmentSource);

    //class_<ShaderParser>("ShaderParser")
    //    .constructor()
    //    .function("LoadFromFile", &ShaderParser::LoadFromFile)
    //    .function("ParseFromString", &ShaderParser::ParseFromString);
}

#endif 