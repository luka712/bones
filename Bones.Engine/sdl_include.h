#pragma once

#ifndef SDL_INCLUDE_H

#define SDL_INCLUDE_H

#include "APP_MACROS.h"

#if EMSCRIPTEN_RUNTIME
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <emscripten/em_js.h>
#include <emscripten/em_asm.h>

// SDL OPENGL 
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GLES3/gl3.h>
#else
// -- SDL OPENGL
// to undefine "main" from sdl
#ifndef SDL_MAIN_HANDLED	
#define SDL_MAIN_HANDLED true
#endif // !SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <gl/glew.h>
#endif

#endif // !SDL_INCLUDE_H
