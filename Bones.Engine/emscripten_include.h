#pragma once

#include "APP_MACROS.h"

#ifndef EMSCRIPTEN_INCLUDE_H

#define EMSCRIPTEN_INCLUDE_H

#if EMSCRIPTEN_RUNTIME
#include <emscripten.h>
#include <emscripten/bind.h>
#include <emscripten/html5.h>
#include <emscripten/em_js.h>
#include <emscripten/em_asm.h>
#endif

#endif // !EMSCRIPTEN_INCLUDE_H
