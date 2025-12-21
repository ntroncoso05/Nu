#pragma once

#ifdef NU_PLATFORM_WINDOWS

extern Nu::Application* Nu::CreateApplication();

int main(int argc, char** argv)
{
	Nu::Log::Init();
	NU_CORE_WARN("Initialized Log!");
	int a = 5;
	NU_INFO("Hello! Var={0}", a);

	auto app = Nu::CreateApplication();
	app->run();
	delete app;
}

#endif // NU_PLATFORM_WINDOWS
