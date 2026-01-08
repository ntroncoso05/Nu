#include "nupch.h"
#include "VertexArray.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nu {

	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetApi())
		{
			case RendererAPI::None:		NU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		NU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}