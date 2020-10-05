#include "actor.hpp"
#include "log.hpp"

namespace Steel
{
	void Actor::AddComponent(StrongActorComponentPtr component)
	{
        component->SetOwner(weak_from_this());
		ActorComponentId component_id(typeid(*component));
		actor_components[component_id] = component;
	}
}