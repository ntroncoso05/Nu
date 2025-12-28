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
		if (Nu::Input::IsKeyPressed(NU_KEY_TAB))
			NU_TRACE("Tab key is pressed (poll)!");
	}

	void OnEvent(Nu::Event& event) override
	{
		if (event.GetEventType() == Nu::EventType::KeyPressed)
		{
			Nu::KeyPressedEvent& e = (Nu::KeyPressedEvent&)event;
			if (e.GetKeyCode() == NU_KEY_TAB)
				NU_TRACE("Tab key is pressed (event)!");
			NU_TRACE("{0}", (char)e.GetKeyCode());
		}
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