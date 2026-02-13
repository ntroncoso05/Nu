#include "nupch.h"
#include "Scene.h"

#include "Component.h"
#include "Nu/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

#include "Entity.h"

namespace Nu {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

	Scene::Scene()
	{
		//entt::entity entity = m_Registry.create();

		//m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
	}

	Scene::~Scene()
	{
	}

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);
			Renderer2D::DrawQuad(transform.Transform, sprite.Color);
		}
	}

}