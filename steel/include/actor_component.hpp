#pragma once

#include <typeindex>

#include "core.hpp"
#include "id_provider.hpp"

namespace Steel
{

using ActorComponentId = std::type_index;

class ActorComponent
{
private:
	
protected:
	bool is_destroyed;
    WeakActorPtr owner;
	ActorComponentId component_id;
		
	ActorComponent(ActorComponentId component_id, WeakActorPtr owner=WeakActorPtr())
		:
		component_id(component_id),
        owner(owner)
	{
		is_destroyed = false;
	}
	
public:
	virtual ActorComponentId GetId() { return component_id; }
	virtual WeakActorPtr GetOwner() { return owner; }
	virtual void SetOwner(WeakActorPtr owner);
		
	virtual void Init() {}
	virtual void PostInit() {}
	virtual void Update(float delta_time) {}
		
	virtual void Destroy() {}
};

}