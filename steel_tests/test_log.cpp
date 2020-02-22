#include <catch2/catch.hpp>
#include "steel.hpp"

TEST_CASE("test_log", "") 
{
	if (!Steel::Log::GetClientLogger())
		Steel::Log::Init();
	
	STEEL_CORE_TRACE("Testing log trace");
	STEEL_CORE_INFO("Testing log info");
	STEEL_CORE_WARN("Testing log warning");
	STEEL_CORE_ERROR("Testing log error");
	STEEL_CORE_CRITICAL("Testing log critical");

	//STEEL_CORE_ASSERT(0, "Expected to be 1");
	//STEEL_ASSERT(0, "Expected to be foo");
}
