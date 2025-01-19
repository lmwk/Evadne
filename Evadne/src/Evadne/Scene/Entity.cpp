#include "evpch.h"
#include "Entity.h"

namespace Evadne {

    Entity::Entity(entt::entity handle, Scene* scene)
        : m_EntityHandle(handle), m_Scene(scene) 
    { 
    }

}