#include <Nu.h>
#include <Nu/Core/EntryPoint.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <ImGui/imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class ExampleLayer : public Nu::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_CameraController(1280.0f / 720.0f) /*<- Aspect ratio 16:9*/
	{
		// Vertex Array
		m_VertexArray = Nu::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		// Vertex Buffer
		Nu::Ref<Nu::VertexBuffer> vertexBuffer = Nu::VertexBuffer::Create(vertices, sizeof(vertices));
		Nu::BufferLayout layout = {
			{ Nu::ShaderDataType::Float3, "a_Position" },
			{ Nu::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// Index Buffer
		uint32_t indices[3] = { 0, 1, 2 };
		Nu::Ref<Nu::IndexBuffer> indexBuffer = Nu::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// Square Vertex Array
		m_SquareVA = Nu::VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		// Square Vertex Buffer
		Nu::Ref<Nu::VertexBuffer> squareVB = Nu::VertexBuffer::Create(squareVertices, sizeof(squareVertices));
		squareVB->SetLayout({
			{ Nu::ShaderDataType::Float3, "a_Position" }, // attributes
			{ Nu::ShaderDataType::Float2, "a_TexCoord" }
		});
		m_SquareVA->AddVertexBuffer(squareVB);

		// Square Index Buffer
		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Nu::Ref<Nu::IndexBuffer> squareIB = Nu::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t));
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

		m_Shader = Nu::Shader::Create("VertexPosColor", vertexSrc, fragmentSrc);

		std::string flatColorShaderVertexSrc = R"(
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

		std::string flatColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color; // output color

			in vec3 v_Position; // variables that are transmitted between shaders are called (varying variables)

			uniform vec3 u_Color;
			
			void main()
			{
				color = vec4(u_Color, 1.0f);
			}
		)";

		m_FlatColorShader = Nu::Shader::Create("FlatColor", flatColorShaderVertexSrc, flatColorShaderFragmentSrc);

		auto textureShader = m_ShaderLibrary.Load("assets/shaders/Texture.glsl");

		m_Texture = Nu::Texture2D::Create("assets/textures/Checkerboard.png");
		m_PlayerTexture = Nu::Texture2D::Create("assets/textures/player.png");

		std::dynamic_pointer_cast<Nu::OpenGLShader>(textureShader)->Bind();
		std::dynamic_pointer_cast<Nu::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);
	}

	void OnUpdate(Nu::Timestep ts) override
	{
		// Update
		m_CameraController.OnUpdate(ts);

		// Render
		Nu::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
		Nu::RenderCommand::Clear();

		Nu::Renderer::BeginScene(m_CameraController.GetCamera());

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Nu::OpenGLShader>(m_FlatColorShader)->Bind();
		std::dynamic_pointer_cast<Nu::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat3("u_Color", m_SquareColor);

		// Square
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Nu::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
			}

		}

		auto textureShader = m_ShaderLibrary.Get("Texture");

		m_Texture->Bind();
		Nu::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		m_PlayerTexture->Bind();
		Nu::Renderer::Submit(textureShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// Triangle
		//Nu::Renderer::Submit(m_Shader, m_VertexArray);

		Nu::Renderer::EndScene();
	}

	virtual void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_SquareColor));
		ImGui::End();
	}

	void OnEvent(Nu::Event& e) override
	{
		m_CameraController.OnEvent(e);
	}
private:
	Nu::ShaderLibrary m_ShaderLibrary;
	Nu::Ref<Nu::Shader> m_Shader;
	Nu::Ref<Nu::VertexArray> m_VertexArray;

	Nu::Ref<Nu::Shader> m_FlatColorShader;
	Nu::Ref<Nu::VertexArray> m_SquareVA;

	Nu::Ref<Nu::Texture2D> m_Texture, m_PlayerTexture;

	Nu::OrthographicCameraController m_CameraController;
	glm::vec3 m_SquareColor = { 0.2f, 0.3f, 0.8f };
};

class Sandbox : public Nu::Application
{
public:
	Sandbox()
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Nu::Application* Nu::CreateApplication()
{
	return new Sandbox();
}