#pragma once

#include "Core.h"

#include "Window.h"
#include "Nu/LayerStack.h"
#include "Nu/Events/Event.h" // Nu/ not needed
#include "Nu/Events/ApplicationEvent.h"

#include <Nu/ImGui/ImGuiLayer.h>

#include "Nu/Renderer/Shader.h"
#include "Nu/Renderer/Buffer.h"
#include "Nu/Renderer/VertexArray.h"

namespace Nu {

	class NU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		inline static Application& Get() { return *s_Instance; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<Shader> m_Shader;
		std::shared_ptr<VertexArray> m_VertexArray;

		std::shared_ptr<Shader> m_BlueShader;
		std::shared_ptr<VertexArray> m_SquareVA;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


