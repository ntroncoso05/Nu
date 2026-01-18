#pragma once

#include "Nu/Renderer/VertexArray.h"

namespace Nu {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override; // probably can't have more than one index buffer

		virtual const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; }
		virtual const Ref<IndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; }
	private:
		uint32_t m_RendererID;
		std::vector<Ref<VertexBuffer>> m_VertexBuffers;	// contains references to every vertex buffer, same as OpenGL does internally, it is mimicking or mirroring that on the CPU
		Ref<IndexBuffer> m_IndexBuffer;					// contains reference to Index buffer, same as OpenGL does internally, it is mimicking or mirroring that on the CPU
	};

}