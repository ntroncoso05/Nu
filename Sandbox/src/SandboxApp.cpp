#include <Nu.h>

class ExampleLayer : public Nu::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		NU_INFO("ExampleLayer::Update");
	}

	void OnEvent(Nu::Event& event) override
	{
		NU_TRACE("{0}", event);
	}
};

class Sandbox : public Nu::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Nu::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Nu::Application* Nu::CreateApplication()
{
	return new Sandbox();
}