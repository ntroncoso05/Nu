#include <Nu.h>

#include "ImGui/imgui.h"

#include <glm/gtc/matrix_transform.hpp>

class ExampleLayer : public Nu::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f) /*Aspect ratio 16:9*/, m_CameraPosition(0.0f)
	{
		// Vertex Array
		m_VertexArray.reset(Nu::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		// Vertex Buffer
		std::shared_ptr<Nu::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Nu::VertexBuffer::Create(vertices, sizeof(vertices)));
		Nu::BufferLayout layout = {
			{ Nu::ShaderDataType::Float3, "a_Position" },
			{ Nu::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		std::shared_ptr<Nu::IndexBuffer> indexBuffer;
		indexBuffer.reset(Nu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square Vertex Array
		m_SquareVA.reset(Nu::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		// Square Vertex Buffer
		std::shared_ptr<Nu::VertexBuffer> squareVB;
		squareVB.reset(Nu::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Nu::ShaderDataType::Float3, "a_Position" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		// Square Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Nu::IndexBuffer> squareIB;
		squareIB.reset(Nu::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		// A uniform is a per draw call kind of value to set to the shader from the CPU side (C++ side in this case)
		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position; // variables that are transmitted between shaders are called (varying variables)
			out vec4 v_Color;
			
			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color; // output color

			in vec3 v_Position; // variables that are transmitted between shaders are called (varying variables)
			in vec4 v_Color;
			
			void main()
			{
				//color = vec4(0.8f, 0.2f, 0.3f, 1.0f);
				color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Nu::Shader(vertexSrc, fragmentSrc));

		std::string blueShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position; // variables that are transmitted between shaders are called (varying variables)
			
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
			}
		)";

		std::string blueShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color; // output color

			in vec3 v_Position; // variables that are transmitted between shaders are called (varying variables)
			
			void main()
			{
				color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
			}
		)";

		m_BlueShader.reset(new Nu::Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
	}

	void OnUpdate(Nu::Timestep ts) override
	{
		if (Nu::Input::IsKeyPressed(NU_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		else if (Nu::Input::IsKeyPressed(NU_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;

		if (Nu::Input::IsKeyPressed(NU_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;
		else if (Nu::Input::IsKeyPressed(NU_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;

		if (Nu::Input::IsKeyPressed(NU_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed * ts;
		else if (Nu::Input::IsKeyPressed(NU_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed * ts;

		Nu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Nu::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Nu::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		// Square
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Nu::Renderer::Submit(m_BlueShader, m_SquareVA, transform);
			}

		}

		// Triangle
		Nu::Renderer::Submit(m_Shader, m_VertexArray);

		Nu::Renderer::EndScene();
		
	}

	virtual void OnImGuiRender() override
	{
		
	}

	void OnEvent(Nu::Event& event) override
	{
	}
private:
	std::shared_ptr<Nu::Shader> m_Shader;
	std::shared_ptr<Nu::VertexArray> m_VertexArray;

	std::shared_ptr<Nu::Shader> m_BlueShader;
	std::shared_ptr<Nu::VertexArray> m_SquareVA;

	Nu::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;
};

class Sandbox : public Nu::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Nu::Application* Nu::CreateApplication()
{
	return new Sandbox();
}