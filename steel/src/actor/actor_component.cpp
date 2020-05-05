#include "actor_component.hpp"
#include "actor.hpp"

namespace Steel
{
	void ActorComponent::SetOwner(StrongActorPtr owner)
	{
		this->owner = owner;
	}
}