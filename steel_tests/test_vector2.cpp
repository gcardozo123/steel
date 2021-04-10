#include <catch2/catch.hpp>
#include "steel.hpp"

using namespace Steel;
TEST_CASE("test_vector2", "") 
{
	Math::Vector2 v;
	REQUIRE(v.x == 0.0);
	REQUIRE(v.y == 0.0);

	v.x = 42.0;
	v.y = 666.0;

	REQUIRE(v.x == 42.0);
	REQUIRE(v.y == 666.0);

    Math::Vector2 other(666.0, 42.0);
	REQUIRE(other.x == 666.0);
	REQUIRE(other.y == 42.0);
}

TEST_CASE("test_vector2_operations", "")
{
    Math::Vector2 v {10, 20};
    Math::Vector2 vv { 5, -12};

    REQUIRE(v + vv == Math::Vector2(15, 8));
    REQUIRE(-v == Math::Vector2(-10, -20));
    REQUIRE(v - vv == Math::Vector2(5, 32));

    v += vv;
    REQUIRE(v == Math::Vector2(15, 8));
    v -= vv;
    REQUIRE(v == Math::Vector2(10, 20));

    v = vv;
    REQUIRE(v == Math::Vector2(5, -12));
    v.x = 42;
    v.y = -42;
    REQUIRE(v == Math::Vector2(42, -42));
    // make sure vv was not modified:
    REQUIRE(vv == Math::Vector2(5, -12));
}
