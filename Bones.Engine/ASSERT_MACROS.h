#pragma once
#ifndef ASSERT_MACROS_H
#define ASSERT_MACROS_H

#include "APP_MACROS.h"

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

#endif