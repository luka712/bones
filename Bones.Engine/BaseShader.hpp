#pragma once 


#include <string>
#include <map>
#include "glm/gtc/type_ptr.hpp"
#include "Constants.hpp"
#include "ShaderParser.hpp"

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
			string m_error;

			ShaderUniformLocationError(const string& error)
			{
				m_error = string("Unable to resolve uniform location ").append(error);
			}

			const char* what() const throw ()
			{
				return m_error.c_str();
			}
		};

		class BaseShader
		{
		protected:
			GLuint m_program, m_vertexShader, m_geometryShader, m_fragmentShader;
			string m_vertexSource, m_geometrySource, m_fragmentSource;
			bool m_initialized;
			map<string, GLint> m_locationsMap;

			GLuint CompileShader(GLenum type, const string& source);
			void Destroy();

		public:
			BaseShader();
			BaseShader(string vertexSource, string fragmentSource);
			BaseShader(string vertexSource, string geometrySource, string fragmentSource);

#pragma region Getters 
			const GLuint& GetProgram() const { return m_program; }
#pragma endregion

#pragma region Framework Methods
			virtual void Load();
			virtual void Initialize();
#pragma endregion

			int GetUniformLocation(const string& uniform);

			void Recompile();

			void UseProgram() const;
			void StopProgram() const;

			void Validate();

			void SetInt(const int& location, int value);
			void SetFloat(const int& location, float value);
			void SetFloat2(const int& location, const glm::vec2& v);
			void SetFloat3(const int& location, const glm::vec3& v);
			void SetFloat4(const int& location, float x, float y, float z, float w);
			void SetFloat4(const int& location, const glm::vec4& v);
			void SetMatrix(const int& location, const glm::mat4& matrix);
			void SetTexture(const int& location, int value);

			void SetFloat(const string& location, float value);
			void SetMatrix(const string& location, const glm::mat4& matrix);
			void SetTexture(const string& location, GLuint textureUnit);


			~BaseShader();
		};

	}
}