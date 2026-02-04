#include "nupch.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

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

	#ifdef NU_ENABLE_ASSERTS
		int versionMajor;
		int versionMinor;
		glGetIntegerv(GL_MAJOR_VERSION, &versionMajor);
		glGetIntegerv(GL_MINOR_VERSION, &versionMinor);

		NU_CORE_ASSERT(versionMajor > 4 || (versionMajor == 4 && versionMinor >= 5), "Nu requieres at least OpenGL version 4.5!");
	#endif
	}

	void OpenGLContext::SwapBuffers()
	{
		NU_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}