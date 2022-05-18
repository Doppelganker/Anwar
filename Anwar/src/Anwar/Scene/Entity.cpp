#include "anwpch.h"
#include "Anwar/Scene/Entity.h"

namespace Anwar
{
    Entity::Entity(entt::entity handle, Scene* scene) : m_EntityHandle(handle), m_Scene(scene)
    {}
}
