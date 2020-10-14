#pragma once

#ifdef PRALINE_DEBUG
	#define PRALINE_ENABLE_ASSERTS
#endif

#ifdef PRALINE_ENABLE_ASSERTS
	#define PRALINE_CORE_ASSERT(x, ...) {if(!(x)) {PRALINE_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
	#define PRALINE_ASSERT(x, ...) {if(!(x)) {PRALINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak();}}
#else
	#define PRALINE_CORE_ASSERT(x, ...)
	#define PRALINE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

