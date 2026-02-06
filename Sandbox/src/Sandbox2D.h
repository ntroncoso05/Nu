#pragma once

#include "Nu.h"

#include "ParticleSystem.h"

class Sandbox2D : public Nu::Layer
{
public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;

	virtual void OnAttach() override; // like the constructor
	virtual void OnDetach() override; // like the destructor

	void OnUpdate(Nu::Timestep ts) override;
	virtual void OnImGuiRender() override;
	void OnEvent(Nu::Event& e) override;
private:
	Nu::OrthographicCameraController m_CameraController;

	// Temp
	Nu::Ref<Nu::Shader> m_FlatColorShader;
	Nu::Ref<Nu::VertexArray> m_SquareVA;

	Nu::Ref<Nu::Texture2D> m_CheckerboardTexture;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };

	ParticleSystem m_ParticleSystem;
	ParticleProps m_Particle;
};