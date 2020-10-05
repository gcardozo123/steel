#include <catch2/catch.hpp>
#include "steel.hpp"

using namespace Steel;
TEST_CASE("test_vector2", "") 
{
	Vector2 v;
	REQUIRE(v.x == 0.0);
	REQUIRE(v.width == 0.0);

	REQUIRE(v.y == 0.0);
	REQUIRE(v.height == 0.0);

	v.x = 42.0;
	v.y = 666.0;

	REQUIRE(v.x == 42.0);
	REQUIRE(v.width == 42.0);
	REQUIRE(v.y == 666.0);
	REQUIRE(v.height == 666.0);

	Vector2 other(666.0, 42.0);
	REQUIRE(other.x == 666.0);
	REQUIRE(other.width == 666.0);
	REQUIRE(other.y == 42.0);
	REQUIRE(other.height == 42.0);
}
