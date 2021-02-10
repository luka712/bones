#include "OpenGL_ES_3_0_Renderer.hpp"
#include "Constants.hpp"
#include <string>

using Bones::Renderer::OpenGL_ES_3_0_Renderer;

#if EMSCRIPTEN_RUNTIME 

// UTF8ToString https://emscripten.org/docs/api_reference/preamble.js.html#UTF8ToString
EM_JS(int, jsGetCanvasWidth, (const char* str, int length), {
  return document.getElementById(UTF8ToString(str, length)).width;
	});

EM_JS(int, jsGetCanvasHeight, (const char* str, int length), {
  return document.getElementById(UTF8ToString(str, length)).height;
	});

#endif 

void OpenGL_ES_3_0_Renderer::CreateWindowAndRenderer()
{
#if EMSCRIPTEN_RUNTIME
	const std::string canvasName = CANVAS_NAME;

	int width = jsGetCanvasWidth(canvasName.c_str(), canvasName.length());
	int height = jsGetCanvasHeight(canvasName.c_str(), canvasName.length());

	if (SDL_CreateWindowAndRenderer(DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL, &m_window, &m_renderer) < 0)
	{
		throw new runtime_error(SDL_GetError());
	}
#else 
	if (SDL_CreateWindowAndRenderer(DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_OPENGL, &m_window, &m_renderer) < 0)
	{
		throw new runtime_error(SDL_GetError());
	}
#endif
}
