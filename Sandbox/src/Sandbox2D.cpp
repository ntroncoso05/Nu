#include "Sandbox2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) /*<- Aspect ratio 16:9*/
{
}

void Sandbox2D::OnAttach()
{
	NU_PROFILE_FUNCTION();

	m_CheckerboardTexture = Nu::Texture2D::Create("assets/textures/Checkerboard.png");
}

void Sandbox2D::OnDetach()
{
	NU_PROFILE_FUNCTION();
}

void Sandbox2D::OnUpdate(Nu::Timestep ts)
{
	NU_PROFILE_FUNCTION();

	// Update
	m_CameraController.OnUpdate(ts);

	// Render
	{
		NU_PROFILE_SCOPE("Renderer Prep");
		Nu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Nu::RenderCommand::Clear();
	}

	{
		NU_PROFILE_SCOPE("Renderer Draw");
		Nu::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Nu::Renderer2D::DrawRotatedQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Nu::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
		Nu::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, m_CheckerboardTexture, 10.0f);
		Nu::Renderer2D::EndScene();
	}
}

void Sandbox2D::OnImGuiRender()
{
	NU_PROFILE_FUNCTION();

	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Nu::Event& e)
{
	m_CameraController.OnEvent(e);
}
