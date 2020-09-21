#pragma once

#include <list>

#include "core.hpp"

namespace Steel
{
    
class ActorManager
{

private:
    std::list<SharedPtr<Actor>> actors;

public:

    ActorManager() {}
    SharedPtr<Actor> CreateActor();
    void Update(double dt);
	
    std::list<SharedPtr<Actor>> GetAllActors() { return actors; }

};

}