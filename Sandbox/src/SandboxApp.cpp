#include <Nu.h>

class Sandbox : public Nu::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Nu::Application* Nu::CreateApplication()
{
	return new Sandbox();
}