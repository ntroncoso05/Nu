#include "nupch.h"
#include "Application.h"

#include "Nu/Events/ApplicationEvent.h"
#include "Nu/Log.h"

#include <GLFW/glfw3.h>

namespace Nu {

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create()); // explicit constructor need std::unique_ptr<Window>()
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

}
