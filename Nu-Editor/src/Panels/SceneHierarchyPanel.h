#pragma once

#include "Nu/Core/Core.h"
#include "Nu/Core/Log.h"
#include "Nu/Scene/Scene.h"
#include "Nu/Scene/Entity.h"

namespace Nu {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetContext(const Ref<Scene>& context);

		void OnImGuiRender();
	private:
		void DrawEntityNode(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};

}
