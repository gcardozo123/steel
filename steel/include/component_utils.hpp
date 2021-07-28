#pragma once

#include <functional>

#include "entt.hpp"

namespace Steel
{

class ComponentUtils
{
    using Func = std::function<void (entt::entity)>;

public:
    static void ForEachDirectChild( entt::registry& world, entt::entity parent, const Func&& func );
    static entt::entity AddChild( entt::registry& world, entt::entity parent );
    static entt::entity GetChild( entt::registry& world, entt::entity parent, int index );
};

}