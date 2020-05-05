#include "actor.hpp"
#include "core.hpp"
#include "log.hpp"

namespace Steel
{
	void Actor::AddComponent(StrongActorComponentPtr component)
	{
		ActorComponentId component_id(typeid(*component));
		actor_components[component_id] = component;
		STEEL_CORE_ASSERT(&(*component->GetOwner()) == &(*this), "This actor must own this component");
	}
}