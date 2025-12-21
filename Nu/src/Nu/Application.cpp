#include "Application.h"

#include "Nu/Events/ApplicationEvent.h"
#include "Nu/Log.h"

namespace Nu {

	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::run()
	{
		WindowResizeEvent e(1280, 720);
		if (e.IsInCategory(EventCategoryApplication))
		{
			NU_TRACE(e);
		}

		if (e.IsInCategory(EventCategoryInput))
		{
			NU_TRACE(e);
		}

		while (true);
	}

}
