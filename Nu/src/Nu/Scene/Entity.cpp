#include "nupch.h"
#include "Entity.h"

namespace Nu {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}