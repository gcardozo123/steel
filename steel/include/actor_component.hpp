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
		StrongActorPtr owner;
		ActorComponentId component_id;
		
		ActorComponent(StrongActorPtr owner, ActorComponentId component_id)
			:
			component_id(component_id)
		{
			is_destroyed = false;
			this->owner = owner;
		}
	
	public:
		virtual ActorComponentId GetId() { return component_id; }
		virtual StrongActorPtr GetOwner() { return owner; }
		virtual void SetOwner(StrongActorPtr owner);
		
		virtual void Init() {}
		virtual void PostInit() {}
		virtual void Update(float delta_time) {}
		
		virtual void Destroy() {}
	};
}