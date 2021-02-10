#pragma once 

#include <string>
#include <map>
#include "FileLoader.hpp"
#include "Constants.hpp"

using namespace std;

#ifndef SHADER_PARSING_VARS

#define SHADER_PARSING_VARS
#define VAR_VERTEX_SHADER "VERTEX_SHADER"
#define VAR_FRAGMENT_SHADER "FRAGMENT_SHADER"
#define VAR_GEOMETRY_SHADER "GEOMETRY_SHADER"
#define VAR_VERSION "#version"

#endif // SHADER_PARSING_VARS! 


namespace Bones
{
	namespace Loaders
	{
		struct ShaderSourceData final
		{
			string vertexSource;
			string geometrySource;
			string fragmentSource;
		};

		/*
			Expect shader to begin from #VERTEX_SHADER, #FRAGMENT_SHADER
		*/
		class ShaderParser final
		{
		private:
			const string m_vertexShaderVar = string(VAR_VERTEX_SHADER);
			const string m_fragmentShaderVar = string(VAR_FRAGMENT_SHADER);
			const string m_geometryShaderVar = string(VAR_GEOMETRY_SHADER);
			const string m_versionVar = string(VAR_VERSION);
		public:
			/// <summary>
			/// Parse the shader.
			/// </summary>
			/// <param name="text">The source.</param>
			/// <returns>ShaderSourceData</returns>
			ShaderSourceData ParseFromString(string& text) const;

			/// <summary>
			/// Load shader from file path.
			/// </summary>
			/// <param name="filepath">The filepath</param>
			/// <returns>ShaderSourceData</returns>
			ShaderSourceData LoadFromFile(const string& filepath) const;

			/// <summary>
			/// Parse the shader.
			/// </summary>
			/// <param name="text">The source.</param>
			/// <param name="shaderReplace">Replace some of options in shader.</param>
			/// <returns>ShaderSourceData</returns>
			ShaderSourceData ParseFromString(string& text, map<string, int> shaderReplace) const;

			/// <summary>
			/// Load shader from file path.
			/// </summary>
			/// <param name="filepath">The filepath</param>
			/// <param name="shaderReplace">Replace some of options in shader.</param>
			/// <returns>ShaderSourceData</returns>
			ShaderSourceData LoadFromFile(const string& filepath, map<string, int> shaderReplace) const;
		};

	}
}

