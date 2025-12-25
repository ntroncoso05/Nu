#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Nu/Events/ApplicationEvent.h"

#include "Window.h"

namespace Nu {

	class NU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();

		void OnEvent(Event& e);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


