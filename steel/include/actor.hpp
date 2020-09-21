#pragma once

#include <unordered_map>
#include <memory>

#include "core.hpp"
#include "id_provider.hpp"
#include "actor_component.hpp"

namespace Steel
{

using ActorId = unsigned int;
using ActorComponents = std::unordered_map<ActorComponentId, StrongActorComponentPtr>;
	
class Actor
{
private:
protected:
	ActorId actor_id;
	ActorComponents actor_components;
		
	//TODO: StrongActorComponentPtr transform;

public:
		
	Actor() { actor_id = IdProvider::New(); }
		
	virtual void Init() {}
	virtual void PostInit() {}
	virtual void Update(float delta_time) {}
	virtual void Destroy() {}
	
	template <class ComponentType>
	std::weak_ptr<ComponentType> GetComponent()
	{
		ActorComponentId component_id(typeid(ComponentType)); 

		auto it = actor_components.find(component_id);
		if (it == actor_components.end())
			return std::weak_ptr<ComponentType>();

		// cast to subclass version of the pointer
		std::shared_ptr<ComponentType> shared(std::static_pointer_cast<ComponentType>(it->second));  
		std::weak_ptr<ComponentType> wp(shared);
		return wp;
	}

	template <class ComponentType>
	bool HasComponent()
	{
		return actor_components.count(ActorComponentId(typeid(ComponentType))) > 0;
	}

	void AddComponent(StrongActorComponentPtr component);
	
};

}