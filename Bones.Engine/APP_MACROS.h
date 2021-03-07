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

#define UNIT_TEST 0

#if TARGET_OPENGL_4_6
#define SHADER_SUFFIX "_v460.shader"
#else 
#define SHADER_SUFFIX "_v300es.shader"
#endif

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#define DEFAULT_WIDTH 1600
#define DEFAULT_HEIGHT 900

#define MAX_DIRECTIONAL_LIGHTS 4
#define MAX_POINT_LIGHTS 4
#define MAX_SPOT_LIGHTS 4

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

#endif // !APP_MACROS_H
