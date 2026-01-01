#pragma once

#include "Nu/Renderer/GraphicsContext.h"

struct GLFWwindow; // forward declaration, to avoid include it

namespace Nu {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};

}