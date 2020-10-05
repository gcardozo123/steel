#include "actor_component.hpp"
#include "actor.hpp"

namespace Steel
{
	void ActorComponent::SetOwner(WeakActorPtr owner)
	{
		this->owner = owner;
	}
}