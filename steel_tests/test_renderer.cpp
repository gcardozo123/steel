#include <catch2/catch.hpp>
#include "steel.hpp"

TEST_CASE("Renderer initialization", "") 
{
	Steel::Renderer renderer;
	REQUIRE( renderer.GetWindowWidth() == 0 );
	REQUIRE( renderer.GetWindowWidth() == 0 );
	REQUIRE( renderer.GetDesiredFps() == 60 );
	REQUIRE( renderer.GetTimeScale() == Approx(1.00f) );
}
