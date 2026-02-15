#include "nupch.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Nu/Core/Input.h"

#include "Nu/Events/ApplicationEvent.h"
#include "Nu/Events/MouseEvent.h"
#include "Nu/Events/KeyEvent.h"

#include "Nu/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLContext.h"

namespace Nu {

	static uint8_t s_GLFWWindowCount = 0;

	static void GLFWErrorCallback(int error, const char* description)
	{
		NU_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		NU_PROFILE_FUNCTION();

		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		NU_PROFILE_FUNCTION();

		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		NU_PROFILE_FUNCTION();

		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		NU_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (s_GLFWWindowCount == 0)
		{			
			NU_PROFILE_SCOPE("glfwInit"); // TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			NU_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
			NU_PROFILE_SCOPE("glfwCreateWindow");
			#if defined(NU_DEBUG)
				if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
					glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
			#endif
			m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
		{				
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window); // User data pointer				
			data.Width = width; // Set the window size values
			data.Height = height;
								
			WindowResizeEvent event(width, height); // Nu event				
			data.EventCallback(event); // Dispatch event
		});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);				
			WindowCloseEvent event; // Nu event				
			data.EventCallback(event); // Dispatch event
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{					
					KeyPressedEvent event(key, 0); // Nu event					
					data.EventCallback(event);	   // Dispatch event
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);// Nu event		
					data.EventCallback(event);	// Dispatch event
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1); // Nu event		
					data.EventCallback(event);	   // Dispatch event
					break;
				}
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			KeyTypedEvent event(keycode);
			data.EventCallback(event);
		});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			switch (action)
			{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
			}
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				
			MouseScrolledEvent event((float)xOffset, (float)yOffset); // Nu event				
			data.EventCallback(event); // Dispatch event
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
								
			MouseMovedEvent event((float)xPos, (float)yPos); // Nu event				
			data.EventCallback(event); // Dispatch event
		});
	}

	void WindowsWindow::Shutdown()
	{
		NU_PROFILE_FUNCTION();

		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate()
	{
		NU_PROFILE_FUNCTION();

		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		NU_PROFILE_FUNCTION();

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