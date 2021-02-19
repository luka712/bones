#pragma once

// APP_MACROS_H holds information that can be considered core and vital for all systems.
// Here you can find information about what runtime to use, what renderer version should be used
// should debug be used, which shader version should be compiled.

#ifndef APP_MACROS_H

#define APP_MACROS_H

// Should build for emscripten
#define EMSCRIPTEN_RUNTIME 0

// Which target version
#define TARGET_OPENGL_ES_3_0 0 // Default, when compiled with emscripten, targets WEBGL_2
#define TARGET_OPENGL_4_6 1  // Newest OPENGL spec
#define TARGET_WEBGL_2_0 (EMSCRIPTEN_RUNTIME && TARGET_OPENGL_ES_3_0) // use in only very specific cases where EMSCRIPTEN_RUNTIME or TARGET_OPENGL_ES_3_0 are not sufficient. 

#define DEBUG 1

#if TARGET_OPENGL_4_6
#define SHADER_SUFFIX "_v460.shader"
#else 
#define SHADER_SUFFIX "_v300es.shader"
#endif

#endif // !APP_MACROS_H
