#pragma once
#include "Nu/Core/Core.h"

#ifdef NU_PLATFORM_WINDOWS

	extern Nu::Application* Nu::CreateApplication();

	int main(int argc, char** argv)
	{
		Nu::Log::Init();

		NU_PROFILE_BEGIN_SESSION("Startup", "NuProfile-Startup.json");
		auto app = Nu::CreateApplication();
		NU_PROFILE_END_SESSION();

		NU_PROFILE_BEGIN_SESSION("Runtime", "NuProfile-Runtime.json");
		app->run();
		NU_PROFILE_END_SESSION();

		NU_PROFILE_BEGIN_SESSION("Shutdown", "NuProfile-Shutdown.json");
		delete app;
		NU_PROFILE_END_SESSION();
	}

#endif // NU_PLATFORM_WINDOWS
