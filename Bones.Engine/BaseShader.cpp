#include "BaseShader.hpp"
#include <iostream>

using Bones::Shaders::BaseShader;

BaseShader::BaseShader(U64 shaderFlag)
	: m_program(0), m_vertexShader(0), m_fragmentShader(0), m_geometryShader(0), m_initialized(false), m_shaderFlags(shaderFlag)
{}

BaseShader::BaseShader(string vertexSource, string fragmentSource, U64 shaderFlag)
	: BaseShader(shaderFlag)
{
	m_vertexSource = vertexSource;
	m_fragmentSource = fragmentSource;
}

BaseShader::BaseShader(string vertexSource, string geometrySource, string fragmentSource, U64 shaderFlag)
	:BaseShader(vertexSource, fragmentSource, shaderFlag)
{
	m_geometrySource = geometrySource;
}

GLuint BaseShader::CompileShader(GLenum type, const string& source)
{
	GLuint shader = glCreateShader(type);

	auto src = source.c_str();
	glShaderSource(shader, 1, &src, 0);

	glCompileShader(shader);

	GLint compileSuccess = 0;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &compileSuccess);

	if (compileSuccess == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);

		auto typeString = type == GL_VERTEX_SHADER ? "vertex" : "fragment";
		string error("Compilation error. Shader type: " + string(typeString) + ". Error: " + string(strInfoLog));

		cout << error << endl;
		delete[] strInfoLog;
		glDeleteShader(shader);

		throw ShaderCompilationError(error);
	}

	glAttachShader(m_program, shader);
	return shader;
}


void BaseShader::Initialize()
{
	// if initialized it was already loaded or request for loading was created.
	if (m_initialized) return;

	m_initialized = true;
	m_program = glCreateProgram();

	m_vertexShader = CompileShader(GL_VERTEX_SHADER, m_vertexSource);
	if (m_geometrySource != "")
	{
		m_geometryShader = CompileShader(GL_GEOMETRY_SHADER, m_geometrySource);
	}
	if (m_fragmentSource != "")
	{
		m_fragmentShader = CompileShader(GL_FRAGMENT_SHADER, m_fragmentSource);
	}

	GLint link_success = 0;
	glLinkProgram(m_program);
	glGetProgramiv(m_program, GL_LINK_STATUS, &link_success);
	if (link_success == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, NULL, strInfoLog);

		string error = string("Cannot create program. Error: " + string(strInfoLog));
		cout << error << endl;
		delete[] strInfoLog;

		Destroy();

		throw ShaderCompilationError(error);
	}

	Validate();

	SetupUniforms();

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
}

void Bones::Shaders::BaseShader::SetupUniforms()
{
	if (m_shaderFlags && ShaderFlags::UsesRandomValue)
	{
		GetUniformLocation("u_random");
	}
	if (m_shaderFlags && ShaderFlags::UsesTimeValue)
	{
		GetUniformLocation("u_time");
	}
}

void BaseShader::Load()
{
}

void BaseShader::UseProgram() const
{
	glUseProgram(m_program);
}

void BaseShader::StopProgram() const
{
	glUseProgram(0);
}

void BaseShader::SetTexture(const int& location, int value)
{
	if (location >= 0)
	{
		glUniform1i(location, value);
	}
}


void BaseShader::SetInt(const int& location, int value)
{
	if (location >= 0)
	{
		glUniform1i(location, value);
	}
}

void BaseShader::SetFloat(const int& location, float value)
{
	if (location >= 0)
	{
		glUniform1f(location, value);
	}
}

void BaseShader::SetFloat2(const I32 location, const F32 x, const F32 y)
{
	glUniform2f(location, x, y);
}

void BaseShader::SetFloat2(const I32 location, const glm::vec2& v)
{
	glUniform2f(location, v.x, v.y);
}

void BaseShader::SetFloat3(const int& location, const glm::vec3& v)
{
	if (location >= 0)
	{
		glUniform3f(location, v.x, v.y, v.z);
	}
}


void BaseShader::SetFloat4(const int& location, float x, float y, float z, float w)
{
	if (location >= 0)
	{
		glUniform4f(location, x, y, z, w);
	}
}

void BaseShader::SetFloat4(const int& location, const glm::vec4& v)
{
	if (location >= 0)
	{
		glUniform4f(location, v.x, v.y, v.z, v.w);
	}
}

void BaseShader::SetTexture(const string& location, GLuint textureUnit)
{
	bool found = m_locationsMap.count(location) > 0;
	if (!found)
	{
		GLint loc = GetUniformLocation(location);
		if (loc >= 0)
		{
			m_locationsMap.emplace(location, loc);
			found = true;
		}
	}

	if (found)
	{
		glUniform1i(m_locationsMap.at(location), textureUnit);
	}
}

void BaseShader::SetFloat(const string& location, float value)
{
	bool found = m_locationsMap.count(location) > 0;
	if (!found)
	{
		GLint loc = GetUniformLocation(location);
		if (loc >= 0)
		{
			m_locationsMap.emplace(location, loc);
			found = true;
		}
	}

	if (found)
	{
		glUniform1f(m_locationsMap.at(location), value);
	}
}

void BaseShader::SetMatrix(const string& location, const glm::mat4& matrix)
{
	bool found = m_locationsMap.count(location) > 0;
	if (!found)
	{
		GLint loc = GetUniformLocation(location);
		if (loc >= 0)
		{
			m_locationsMap.emplace(location, loc);
			found = true;
		}
	}

	if (found)
	{
		glUniformMatrix4fv(m_locationsMap.at(location), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}

void BaseShader::SetMatrix(const int& location, const glm::mat4& matrix)
{
	if (location >= 0)
	{
		glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(matrix));
	}
}


Bones::I32 BaseShader::GetUniformLocation(const string& uniform)
{
	I32 loc = glGetUniformLocation(m_program, uniform.c_str());
	if (loc < 0)
	{
		cout << "Cannot find location for uniform: " << uniform << endl;
	}
	else
	{
		m_locationsMap.emplace(uniform, loc);
	}
	return loc;
}

void BaseShader::Recompile()
{
	m_initialized = false;
	Initialize();
}

void BaseShader::Destroy()
{
	if (m_vertexShader > 0)
	{
		glDeleteShader(m_vertexShader);
	}
	if (m_geometryShader > 0)
	{
		glDeleteShader(m_geometryShader);
	}
	if (m_fragmentShader > 0)
	{
		glDeleteShader(m_fragmentShader);
	}
	if (m_program)
	{
		glDeleteProgram(m_program);
	}
}

void BaseShader::Validate()
{
	GLint validate_success = 0;
	glValidateProgram(m_program);
	glGetProgramiv(m_program, GL_VALIDATE_STATUS, &validate_success);
	if (validate_success == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(m_program, infoLogLength, NULL, strInfoLog);

		string error = string("Cannot validate program. Error: " + string(strInfoLog));
		cout << error << endl;
		delete[] strInfoLog;

		Destroy();

		throw ShaderCompilationError(error);
	}
}

BaseShader::~BaseShader()
{
	Destroy();
}


#if EMSCRIPTEN_RUNTIME 

using namespace emscripten;

EMSCRIPTEN_BINDINGS(Shader_JS)
{
	class_<BaseShader>("BaseShader")
		.constructor<string, string>()
		.function("Initialize", &BaseShader::Initialize);
}

#endif 
