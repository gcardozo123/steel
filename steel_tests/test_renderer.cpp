#include <catch2/catch.hpp>
#include "steel.hpp"

using namespace Steel;
TEST_CASE("Renderer initialization", "") 
{
    SharedPtr<ActorManager> actors = CreateSharedPtr<ActorManager>();
    Renderer renderer(actors);
	REQUIRE( renderer.GetWindowWidth() == 0 );
	REQUIRE( renderer.GetWindowWidth() == 0 );
	REQUIRE( renderer.GetDesiredFps() == 60 );
	REQUIRE( renderer.GetTimeScale() == Approx(1.00f) );

    SharedPtr<Steel::GameInfo> game_info = Steel::CreateSharedPtr<Steel::GameInfo>();
    renderer.Initialize(game_info);
    REQUIRE(renderer.GetWindowWidth() == 1280);
    REQUIRE(renderer.GetWindowHeight() == 720);
}
