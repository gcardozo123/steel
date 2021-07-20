#include "component_utils.hpp"
#include "components.hpp"
#include "core.hpp"

namespace Steel
{

void ComponentUtils::ForEachDirectChild( entt::registry& world, entt::entity parent, const ComponentUtils::Func&& func )
{
    RelationshipComponent& parent_relations = world.get<RelationshipComponent>( parent );
    entt::entity current_child{ parent_relations.first_child };
    while ( world.valid( current_child ) )
    {
        func( current_child );
        RelationshipComponent& current_child_relations = world.get<RelationshipComponent>( current_child );
        current_child = current_child_relations.next_sibling;
    }
}

entt::entity ComponentUtils::AddChild( entt::registry& world, entt::entity parent )
{
    //STEEL_CORE_ASSERT( world.valid( parent ), "Trying to add a child to an invalid parent" ); //TODO fix identifier not found

    entt::entity child = world.create();
    world.emplace<TransformComponent>( child );
    RelationshipComponent& child_relations = world.emplace<RelationshipComponent>( child );
    child_relations.parent = parent;

    RelationshipComponent& parent_relations = world.get<RelationshipComponent>( parent );
    if ( !world.valid( parent_relations.first_child ) )
    {
        parent_relations.first_child = child;
        printf("First child: %d\n", child );
        return child;
    }

    entt::entity current_child{ parent_relations.first_child };
    RelationshipComponent* current_child_relations = &world.get<RelationshipComponent>( current_child );
    while ( world.valid( current_child_relations->next_sibling ) )
    {
        current_child = current_child_relations->next_sibling;
        current_child_relations = &world.get<RelationshipComponent>( current_child );
    }
    current_child_relations->next_sibling = child;
    child_relations.prev_sibling = current_child;
    return child;
}

}