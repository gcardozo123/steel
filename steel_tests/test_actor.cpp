#include <catch2/catch.hpp>
#include "steel.hpp"

using namespace Steel;

class ComponentA : public ActorComponent
{
public:
	ComponentA(StrongActorPtr owner)
		: ActorComponent(owner, ActorComponentId(typeid(this)))
	{}
};

class ComponentB : public ActorComponent
{
public:
	ComponentB(StrongActorPtr owner)
		: ActorComponent(owner, ActorComponentId(typeid(this)))
	{}
};

class ComponentC : public ActorComponent
{
public:
	ComponentC(StrongActorPtr owner)
		: ActorComponent(owner, ActorComponentId(typeid(this)))
	{}
};

TEST_CASE("test_actor", "") 
{
	for(int i = 0; i < 10; i++)
		REQUIRE(IdProvider::New() == i + 1);

	StrongActorPtr actor = CreateSharedPtr<Actor>();
	actor->Init();
	actor->PostInit();
	actor->Update(0.1666f);
	// it doesn't have an ComponentA, so it should return an expired weak_ptr:
	REQUIRE(actor->GetComponent<ComponentA>().expired());

	// let's make sure that the component's pointer destruction won't destroy the actor as well
	{
		auto componentA = CreateSharedPtr<ComponentA>(actor);
		REQUIRE(!actor->HasComponent<ComponentA>());
		actor->AddComponent(componentA);
	}
	REQUIRE(actor->HasComponent<ComponentA>());
	REQUIRE(!actor->GetComponent<ComponentA>().expired());
	auto a_owner = actor->GetComponent<ComponentA>().lock()->GetOwner();
	REQUIRE(a_owner != nullptr);
	REQUIRE(a_owner == actor);

	//now let's test with multiple components:
	auto a = CreateSharedPtr<ComponentA>(actor);
	auto b = CreateSharedPtr<ComponentB>(actor);
	auto c = CreateSharedPtr<ComponentC>(actor);
	
	REQUIRE(!actor->HasComponent<ComponentB>());
	actor->AddComponent(b);
	REQUIRE(actor->HasComponent<ComponentB>());
	
	REQUIRE(!actor->HasComponent<ComponentC>());
	actor->AddComponent(c);
	REQUIRE(actor->HasComponent<ComponentC>());

	
	auto a_ptr = actor->GetComponent<ComponentA>().lock();
	REQUIRE(a_ptr != nullptr);

	auto b_ptr = actor->GetComponent<ComponentB>().lock();
	REQUIRE(b_ptr != nullptr);
	
	auto c_ptr = actor->GetComponent<ComponentC>().lock();
	REQUIRE(c_ptr != nullptr);
	
	// let's check that components have the expected IDs:
	REQUIRE(typeid(a_ptr.get()).name() == a->GetId().name());
	REQUIRE(typeid(b_ptr.get()).name() == b->GetId().name());
	REQUIRE(typeid(c_ptr.get()).name() == c->GetId().name());
	
	/*STEEL_CORE_INFO(a.get()->component_id.name());
	STEEL_CORE_INFO(b.get()->component_id.name());
	STEEL_CORE_INFO(c.get()->component_id.name());*/
	//STEEL_CORE_INFO(a_ptr.get() == a);
}
