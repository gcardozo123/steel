#pragma once

#include "log.hpp"

#ifdef STEEL_DEBUG
    #define STEEL_ENABLE_ASSERTS
#endif

#ifdef STEEL_ENABLE_ASSERTS
    #define STEEL_ASSERT(x, ...) { if(!(x)) { STEEL_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
    #define STEEL_CORE_ASSERT(x, ...) { if(!(x)) { STEEL_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
    #define STEEL_ASSERT(x, ...)
	#define STEEL_CORE_ASSERT(x, ...)
#endif