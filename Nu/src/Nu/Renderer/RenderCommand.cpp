#include "nupch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Nu {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;

}