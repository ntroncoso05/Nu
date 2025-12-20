#pragma once

#include "Core.h"

namespace Nu {

	class NU_API Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
	};

	// To be defined in CLIENT
	Application* CreateApplication();
}


