#pragma once 


#include <string>
#include <unordered_map>
#include "core_types.h"
#include "glm/gtc/type_ptr.hpp"
#include "core_types.h"
#include "ShaderParser.hpp"
#include "sdl_include.h"

using namespace std;
using namespace Bones::Loaders;

namespace Bones
{
	namespace Shaders
	{
		struct ShaderCompilationError : public exception
		{
			string m_error;

			ShaderCompilationError(const string& error) : m_error(error) {}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		struct ShaderUniformLocationError : public exception
		{
			std::string m_error;

			ShaderUniformLocationError(const std::string& error)
			{
				m_error = std::string("Unable to resolve uniform location ").append(error);
			}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		enum ShaderFlags
		{
			UsesTimeValue = 1 << 0,
			UsesRandomValue = 1 << 1
		};

		class BaseShader
		{
		public:
			U64 m_shaderFlags;

			// all the shader locations ids where key is for example "u_color" and value of id is 1.
			std::unordered_map<std::string, GLint> m_locationsMap;

			BaseShader(U64 shaderFlag = 0);
			BaseShader(string vertexSource, string fragmentSource, U64 shaderFlag = 0);
			BaseShader(string vertexSource, string geometrySource, string fragmentSource, U64 shaderFlag = 0);

#pragma region Getters 
			const GLuint& GetProgram() const { return m_program; }
#pragma endregion

#pragma region Framework Methods
			virtual void Load();
			virtual void Initialize();
#pragma endregion

			void SetupUniforms();

			/// <summary>
			/// Gets the uniform location id and saves location and uniform into m_locationsMap.
			/// </summary>
			/// <param name="uniform">Name of uniform.</param>
			/// <returns>Id of uniform</returns>
			I32 GetUniformLocation(const string& uniform);

			void Recompile();

			void UseProgram() const;
			void StopProgram() const;

			void Validate();

			void SetInt(const int& location, int value);
			void SetFloat(const int& location, float value);
			void SetFloat2(const I32 location, const glm::vec2& v);
			void SetFloat2(const I32 location, const F32 x, const F32 y);
			void SetFloat3(const int& location, const glm::vec3& v);
			void SetFloat4(const int& location, float x, float y, float z, float w);
			void SetFloat4(const int& location, const glm::vec4& v);
			void SetMatrix(const int& location, const glm::mat4& matrix);
			void SetTexture(const int& location, int value);

			void SetFloat(const string& location, float value);
			void SetMatrix(const string& location, const glm::mat4& matrix);
			void SetTexture(const string& location, GLuint textureUnit);


			~BaseShader();
		protected:
			U32 m_program, m_vertexShader, m_geometryShader, m_fragmentShader;
			std::string m_vertexSource, m_geometrySource, m_fragmentSource;
			bool m_initialized;

			GLuint CompileShader(GLenum type, const string& source);
			void Destroy();

		};

	}
}