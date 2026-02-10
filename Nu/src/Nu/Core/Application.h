#pragma once

#include "Core.h"

#include "Window.h"
#include "Nu/Core/LayerStack.h"
#include "Nu/Events/Event.h"
#include "Nu/Events/ApplicationEvent.h"

#include "Nu/Core/Timestep.h"

#include <Nu/ImGui/ImGuiLayer.h>

int main(int argc, char** argv);

namespace Nu {

	class Application
	{
	public:
		Application(const std::string& name = "Nu App");
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }

		void Close();

		ImGuiLayer* GetImGuiLayer() { return m_ImGuiLayer; }

		static Application& Get() { return *s_Instance; }
	private:
		void run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		Scope<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
		float m_LastFrameTime = 0.0f;
	private:
		static Application* s_Instance;
		friend int::main(int argc, char** argv);
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}