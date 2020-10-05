#include <catch2/catch.hpp>
#include "steel.hpp"

using namespace Steel;
TEST_CASE("test_transform", "") 
{
	StrongActorPtr actor = CreateSharedPtr<Actor>();
	Transform t(actor);
	
	Vector2 position = t.GetPosition();
	REQUIRE(position.x == 0.0);
	REQUIRE(position.y == 0.0);
	
	position.x = 42.0;
	position.y = 666.0;
	REQUIRE(position.x == 42.0);
	REQUIRE(position.y == 666.0);
	REQUIRE(t.GetPosition().x == 0.0);
	REQUIRE(t.GetPosition().y == 0.0);
	
	t.SetPosition(123.0, 321.0);
	REQUIRE(t.GetPosition().x == 123.0);
	REQUIRE(t.GetPosition().y == 321.0);
	
	t.SetOriginalSize(Vector2(64.0, 64.0));
	REQUIRE(t.GetScale().x == 1.0);
	REQUIRE(t.GetScale().y == 1.0);

	t.SetSize(0.0, 0.0);
	REQUIRE(t.GetScale().x == 0.0);
	REQUIRE(t.GetScale().y == 0.0);

	t.SetSize(128.0, 128.0);
	REQUIRE(t.GetScale().x == 2.0);
	REQUIRE(t.GetScale().y == 2.0);
	
	t.SetScale(3.0);
	REQUIRE(t.GetScale().x == 3.0);
	REQUIRE(t.GetScale().y == 3.0);
	REQUIRE(t.GetSize().x == 192.0);
	REQUIRE(t.GetSize().y == 192.0);
	
	t.SetScale(0.5);
	REQUIRE(t.GetSize().x == 32.0);
	REQUIRE(t.GetSize().y == 32.0);
	
}
