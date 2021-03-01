
// --DEPRECATED
#pragma once

#ifndef VENDOR_H

#define VENDOR_H



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
#include <SDL2/SDL_syswm.h>
#include <gl/glew.h>
#endif


#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif



#endif // !VENDOR_H
