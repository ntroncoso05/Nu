#include "nupch.h"
#include "Framebuffer.h"

#include "Nu/Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLFramebuffer.h"

namespace Nu {

	Ref<Framebuffer> Framebuffer::Create(const FrambufferSpecification& spec)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:	NU_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::API::OpenGL:	return CreateRef<OpenGLFramebuffer>(spec);
		}

		NU_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

}