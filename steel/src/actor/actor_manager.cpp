#include "actor_manager.hpp"

#include "log.hpp"
#include "actor.hpp"

#include "texture_component.hpp"

namespace Steel
{

SharedPtr<Actor> ActorManager::CreateActor()
{
    SharedPtr<Actor> actor = CreateSharedPtr<Actor>();
    this->actors.push_back(actor);
    //TODO: call actor->Init(), PostInit, etc when actor is added to scene (or here?)
    auto texture_component = CreateSharedPtr<TextureComponent>(actor);
    actor->AddComponent(texture_component);

    return actor;
}

void ActorManager::Update(double dt)
{
    //STEEL_INFO("update actors: {0}", dt);
    for (auto actor : this->actors)
    {
        actor->Update(dt);
    }
}


}