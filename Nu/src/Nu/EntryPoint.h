#pragma once

#ifdef NU_PLATFORM_WINDOWS

extern Nu::Application* Nu::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Nu::CreateApplication();
	app->run();
	delete app;
}

#endif // NU_PLATFORM_WINDOWS
