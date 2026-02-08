#pragma once

// For use by Nu Applications

#include "Nu/Core/Core.h"

#include "Nu/Core/Application.h"
#include "Nu/Core/Layer.h" // not need it, to be more clear that it should be accesible by the client(Sandbox) ?
#include "Nu/Core/Log.h"

#include "Nu/Core/Timestep.h"

#include "Nu/Core/Input.h"
#include "Nu/Core/KeyCodes.h"
#include "Nu/Core/MouseButtonCodes.h"
#include "Nu/Renderer/OrthographicCameraController.h"

#include "Nu/ImGui/ImGuiLayer.h"

// ---Renderer-------------------------
#include "Nu/Renderer/Renderer.h"
#include "Nu/Renderer/Renderer2D.h"
#include "Nu/Renderer/RenderCommand.h"

#include "Nu/Renderer/Buffer.h"
#include "Nu/Renderer/Shader.h"
#include "Nu/Renderer/Framebuffer.h"
#include "Nu/Renderer/Texture.h"
#include "Nu/Renderer/VertexArray.h"

#include "Nu/Renderer/OrthographicCamera.h"
// ------------------------------------