// Should build for emscripten
#define EMSCRIPTEN_RUNTIME 0

// Which target version
#define TARGET_OPENGL_ES_3_0 0 // Default, when compiled with emscripten, targets WEBGL_2
#define TARGET_OPENGL_4_6 1  // Newest OPENGL spec
#define TARGET_WEBGL_2_0 (EMSCRIPTEN_RUNTIME && TARGET_OPENGL_ES_3_0) // use in only very specific cases where EMSCRIPTEN_RUNTIME or TARGET_OPENGL_ES_3_0 are not sufficient. 

#define DEBUG 1
#define UNIT_TEST 0

#if TARGET_OPENGL_4_6
#define SHADER_SUFFIX "_v460.shader"
#else 
#define SHADER_SUFFIX "_v300es.shader"
#endif


#if EMSCRIPTEN_RUNTIME
#define CANVAS_NAME "canvas"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <emscripten/em_js.h>
#include <emscripten/em_asm.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLES3/gl3.h>
#else
// to undefine "main" from sdl
#ifndef SDL_MAIN_HANDLED	
	#define SDL_MAIN_HANDLED true
#endif // !SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_syswm.h>
#include <gl/glew.h>
#endif

#if DEBUG
#include <stdio.h>
#define LOG_ERROR(FORMAT, ...) fprintf(stderr, "%s() in %s, line %i: " FORMAT "\n", __func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG_FORMAT(FORMAT, ...) fprintf(stdout, "%s() in %s, line %i: " FORMAT "\n", __func__, __FILE__, __LINE__, __VA_ARGS__)
#define LOG(MSG) LOG_FORMAT("%s\n", MSG)
#define LOG_CONSTRUCTOR() LOG("Constructor called.\n")
#define LOG_COPY_CONSTRUCTOR() LOG("Copy constructor called.\n")
#define LOG_COPY_OPERATOR() LOG("Copy operator called.\n")
#define LOG_DESTRUCTOR() LOG("Destructor called.\n")
#define LOG_INITIALIZE() LOG("Initialize called.\n")
#define LOG_LOAD() LOG("Initialize called.\n")
#define LOG_DESTROY() LOG("Initialize called.\n")
#else
#define LOG_ERROR(FORMAT, ...) ((void)0)
#define LOG_FORMAT(FORMAT, ...) ((void)0)
#define LOG(MSG) ((void)0)
#define LOG_CONSTRUCTOR() ((void)0)
#define LOG_COPY_CONSTRUCTOR() 
#define LOG_COPY_OPERATOR() 
#define LOG_DESTRUCTOR() ((void)0)
#define LOG_INITIALIZE() 
#define LOG_LOAD() 
#define LOG_DESTROY() 
#endif

#if DEBUG && EMSCRIPTEN_RUNTIME == false 
	#define ASSERT(EXPR) \
	if(EXPR) {} \
	else {\
	LOG_FORMAT("Assert failed: %s", #EXPR); \
	__debugbreak(); \
	}
#else 
	#define ASSERT(expr)
#endif 

// For warnings, this should be always printed out.
#define LOG_WARN_FORMAT(FORMAT, ...) fprintf(stdout, "%s. Warning: " FORMAT "\n", __func__, __VA_ARGS__)
#define LOG_WARN(MSG) LOG_FORMAT("%s\n", MSG)

// removing of instances.
// Delete ptr
#define DELETE_PTR(PTR) if(PTR != nullptr) { delete PTR; PTR = nullptr; }

// Delete vector and clear pointer
#define DELETE_VECTOR(VECTOR){			              \
	for (unsigned int i = 0; i < VECTOR.size(); i++)  \
		delete VECTOR.at(i);						  \
    VECTOR.clear();									  }

// Delete map
#define DELETE_MAP(MAP){							  \
	for(auto it = MAP.begin(); it != MAP.end(); ++it) \
		delete it->second;							  \
	MAP.clear();									  }

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4

#define DEFAULT_WIDTH 1600
#define DEFAULT_HEIGHT 900

#define DEBUG_SHADERS_PATH "resources/shaders/debug/"
#define SHADOW_SHADERS_PATH "resources/shaders/shadow/"
#define MATERIAL_SHADERS_PATH "resources/shaders/material/"
#define STENCIL_SHADERS_PATH "resources/shaders/stencil/"
#define POSTPROCESS_SHADERS_PATH "resources/shaders/postprocess/"
#define ENVIRONMENT_SHADERS_PATH "resources/shaders/environment/"

#define COLOR_SHADER_PATH "/src/shaders/uniform-color.shader"
#define TEXTURE_SHADER_PATH "/src/shaders/texture.shader"
#define NO_TRANSFORM_COLOR_SHADER_PATH "/src/shaders/no-transform-color.shader"

// UI 
#define UI_ROW_HEIGHT 15
// render loop is running too fast. Use this to update bit of delay whne handling input.
#define UPDATE_INPUT_TIME 100;

#define UI_SELECTED_COLOR_R 0
#define UI_SELECTED_COLOR_G 183
#define UI_SELECTED_COLOR_B 235
#define UI_SELECTED_COLOR_A 200


#ifndef STATE_H

#define STATE_H

namespace Bones
{
	

	/// <summary>
	/// Sets draw mode with or without indices.
	/// Such as glDrawArrays or glDrawElements
	/// </summary>
	enum class DrawMode
	{
		ARRAYS, ELEMENTS
	};

	/// <summary>
	/// Byte size of different types of indices that go to indices buffer.
	/// </summary>
	enum class IndicesByteSize
	{
		// NONE no indices present.
		NONE = 0,
		UNSIGNED_BYTE = 1,
		UNSIGNED_SHORT = 2,
		UNSIGNED_INT = 4
	};

	/// <summary>
	/// Sets types of drawing when calling stuff as glDrawArrays or glDrawElements
	/// for example GL_TRIANGLES, GL_LINES etc... 
	/// </summary>
	enum class DrawType
	{
		POINTS = 0x0000,
		LINES = 0x0001,
		LINE_LOOP = 0x0002,
		LINE_STRIP = 0x0003,
		TRIANGLES = 0x0004,
		TRIANGLE_STRIP = 0x0005,
		TRIANGLE_FAN = 0x0006
	};

	template<typename T>
	struct Event
	{
		T m_callee;
	};

	template <typename T, typename TValue = void*>
	struct ChangeEvent
	{
		T m_callee;
		TValue m_value;
	};
}

#endif // !STATE_H

