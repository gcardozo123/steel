#pragma once

#include <memory>

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

namespace Steel 
{
	template<typename T>
	using UniquePtr = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr UniquePtr<T> CreateUniquePtr(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using SharedPtr = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr SharedPtr<T> CreateSharedPtr(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}

}