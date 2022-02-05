#pragma once

#include "core.hpp"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace Steel
{
	class Log
	{
	public:
		static void Init();

		static SharedPtr<spdlog::logger>& GetCoreLogger() { return static_core_logger; }
		static SharedPtr<spdlog::logger>& GetClientLogger() { return static_client_logger; }
	private:
		static SharedPtr<spdlog::logger> static_core_logger;
		static SharedPtr<spdlog::logger> static_client_logger;
	};
}

#ifdef STEEL_ENABLE_LOG
	// Core log macros
	#define STEEL_CORE_TRACE(...)    ::Steel::Log::GetCoreLogger()->trace(__VA_ARGS__)
	#define STEEL_CORE_INFO(...)     ::Steel::Log::GetCoreLogger()->info(__VA_ARGS__)
	#define STEEL_CORE_WARN(...)     ::Steel::Log::GetCoreLogger()->warn(__VA_ARGS__)
	#define STEEL_CORE_ERROR(...)    ::Steel::Log::GetCoreLogger()->error(__VA_ARGS__)
	#define STEEL_CORE_CRITICAL(...) ::Steel::Log::GetCoreLogger()->critical(__VA_ARGS__)

	// Client log macros			   
	#define STEEL_TRACE(...)         ::Steel::Log::GetClientLogger()->trace(__VA_ARGS__)
	#define STEEL_INFO(...)          ::Steel::Log::GetClientLogger()->info(__VA_ARGS__)
	#define STEEL_WARN(...)          ::Steel::Log::GetClientLogger()->warn(__VA_ARGS__)
	#define STEEL_ERROR(...)         ::Steel::Log::GetClientLogger()->error(__VA_ARGS__)
	#define STEEL_CRITICAL(...)      ::Steel::Log::GetClientLogger()->critical(__VA_ARGS__)
#else
	// Core log macros
	#define STEEL_CORE_TRACE(...)    
	#define STEEL_CORE_INFO(...)     
	#define STEEL_CORE_WARN(...)     
	#define STEEL_CORE_ERROR(...)    
	#define STEEL_CORE_CRITICAL(...) 

	// Client log macros
	#define STEEL_TRACE(...)         
	#define STEEL_INFO(...)          
	#define STEEL_WARN(...)          
	#define STEEL_ERROR(...)         
	#define STEEL_CRITICAL(...)      
#endif
