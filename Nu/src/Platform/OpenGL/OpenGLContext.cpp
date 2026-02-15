#include "nupch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nu {	

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		NU_CORE_ASSERT(windowHandle, "Window handle is null!");
	}

	void OpenGLContext::Init()
	{
		NU_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NU_CORE_ASSERT(status, "Failed to initialized Glad!");

		NU_CORE_INFO("OpenGL Info:");
		NU_CORE_INFO("  Vendor: {0}",	(const char*)glGetString(GL_VENDOR));
		NU_CORE_INFO("  Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		NU_CORE_INFO("  Version: {0}",	(const char*)glGetString(GL_VERSION));

		NU_CORE_ASSERT(GLVersion.major > 4 || (GLVersion.major == 4 && GLVersion.minor >= 5), "Hazel requires at least OpenGL version 4.5!");
	}

	void OpenGLContext::SwapBuffers()
	{
		NU_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}
