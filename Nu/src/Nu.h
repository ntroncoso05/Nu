#pragma once

// For use by Nu Applications

#include "Nu/Application.h"
#include "Nu/Layer.h" // not need it, to be more clear that it should be accesible by the client(Sandbox) 
#include "Nu/Log.h"

#include "Nu/Core/Timestep.h"

#include "Nu/Input.h"
#include "Nu/KeyCodes.h"
#include "Nu/MouseButtonCodes.h"

#include "Nu/ImGui/ImGuiLayer.h"

// ---Renderer-------------------------
#include "Nu/Renderer/Renderer.h"
#include "Nu/Renderer/RenderCommand.h"

#include "Nu/Renderer/Buffer.h"
#include "Nu/Renderer/Shader.h"
#include "Nu/Renderer/Texture.h"
#include "Nu/Renderer/VertexArray.h"

#include "Nu/Renderer/OrthographicCamera.h"
// ------------------------------------

// ---Entry Point----------------------
#include "Nu/EntryPoint.h"
// ------------------------------------