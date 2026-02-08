#include "Sandbox2D.h"
#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f) /*<- Aspect ratio 16:9*/, m_SquareColor({ 0.2f, 0.3f, 0.8f, 1.0f })
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
	Nu::Renderer2D::ResetStats(); // Reset Stats here
	{
		NU_PROFILE_SCOPE("Renderer Prep");
		Nu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Nu::RenderCommand::Clear();
	}

	{
		static float rotation = 0.0f;
		rotation += ts * 50.0f;

		NU_PROFILE_SCOPE("Renderer Draw");
		Nu::Renderer2D::BeginScene(m_CameraController.GetCamera());
		Nu::Renderer2D::DrawRotatedQuad({ 1.0f, 0.0f }, { 0.8f, 0.8f }, glm::radians(-45.0f), { 0.8f, 0.2f, 0.3f, 1.0f });
		Nu::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
		Nu::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, m_SquareColor);
		Nu::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 20.0f, 20.0f }, m_CheckerboardTexture, 10.0f);
		Nu::Renderer2D::DrawRotatedQuad({ -2.0f, -0.0f, 0.0f }, { 1.0f, 1.0f }, glm::radians(rotation), m_CheckerboardTexture, 20.0f);
		Nu::Renderer2D::EndScene();

		Nu::Renderer2D::BeginScene(m_CameraController.GetCamera());
		for (float y = -5.0f; y < 5.0f; y += 0.5f)
		{
			for (float x = -5.0f; x < 5.0f; x += 0.5f)
			{
				glm::vec4 colorGradient = { (x + 5.0f) / 10.0f, 0.4f, (y + 5.0f) / 10.0f, 0.7f };
				Nu::Renderer2D::DrawQuad({ x, y }, { 0.45f, 0.45f }, colorGradient);
			}
		}
		Nu::Renderer2D::EndScene();
	}

	Nu::Renderer2D::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	NU_PROFILE_FUNCTION();	

	ImGui::Begin("Settings");

	auto stats = Nu::Renderer2D::GetStats();
	ImGui::Text("Renderer2D Stats:");
	ImGui::Text("Draw Calls: %d", stats.DrawCalls);
	ImGui::Text("Quads: %d", stats.QuadCount);
	ImGui::Text("Vertices: %d", stats.GetTotalVertexCount());
	ImGui::Text("Indices: %d", stats.GetTotalIndexCount());

	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Nu::Event& e)
{
	m_CameraController.OnEvent(e);
}
