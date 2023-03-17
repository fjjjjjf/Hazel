#pragma once

#ifdef  HZ_PLATFORM_WINDOWS
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API _declspec(dllexport)
	#else
		#define HAZEL_API _declspec(dllimport)
	#endif // DEBUG
#else
	#error Hazel only support Windows!
#endif //  HZ_PLATFORM_WINDOWS

#ifdef HZ_ENABLE_ASSERTS
	#define HZ_ASSERT(X, ...) {if(!(x)){HZ_ERROR("Asseertion Failed: {0}",__VA_ARGS__);__debugbreak();} }
	#define HZ_CORE_ASSERT(x,...){if (!(x)) {HZ_CORE_ERROR("Assertion Failed:{0}",__VA_ARGS__);__debugbreak();}}
#else
	#define HZ_ASSERT(X, ...)
	#define HZ_CORE_ASSERT(x,...)
#endif // HZ_ENABLE_ASSERTS


#define BIT(X) (1 << X)