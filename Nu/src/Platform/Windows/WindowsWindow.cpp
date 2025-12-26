#include "nupch.h"
#include "WindowsWindow.h"

#include "Nu/Events/ApplicationEvent.h"
#include "Nu/Events/KeyEvent.h"
#include "Nu/Events/MouseEvent.h"

#include <glad/glad.h>

namespace Nu {

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NU_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NU_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			NU_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NU_CORE_ASSERT(status, "Failed to initialized Glad!");
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, 
			[](GLFWwindow* window, int width, int height)
			{
				// User data pointer
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				// Set the window size values
				data.Width = width;
				data.Height = height;

				// Nu event
				WindowResizeEvent event(width, height);
				// Dispatch event
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, 
			[](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				// Nu event
				WindowCloseEvent event;
				// Dispatch event
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window,
			[](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						// Nu event
						KeyPressedEvent event(key, 0);
						// Dispatch event
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						// Nu event
						KeyReleasedEvent event(key);
						// Dispatch event
						data.EventCallback(event);
						break;
					}
					case GLFW_REPEAT:
					{
						// Nu event
						KeyPressedEvent event(key, 1);
						// Dispatch event
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetCharCallback(m_Window,
			[](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window,
			[](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						// Nu event
						MouseButtonPressedEvent event(button);
						// Dispatch event
						data.EventCallback(event);
						break;
					}
					case GLFW_RELEASE:
					{
						// Nu event
						MouseButtonReleasedEvent event(button);
						// Dispatch event
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window,
			[](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				// Nu event
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				// Dispatch event
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window,
			[](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				// Nu event
				MouseMovedEvent event((float)xPos, (float)yPos);
				// Dispatch event
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}