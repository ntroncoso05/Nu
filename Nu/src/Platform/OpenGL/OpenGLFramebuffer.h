#pragma once

#include "Nu/Renderer/Framebuffer.h"

namespace Nu {

	class OpenGLFramebuffer : public Framebuffer
	{
	public:
		OpenGLFramebuffer(const FrambufferSpecification& spec);
		virtual ~OpenGLFramebuffer();

		void Invalidate(); // State not valid recreate

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }; // to bind as a texture to pass to ImGui

		virtual const FrambufferSpecification& GetSpecification() const override { return m_Specification; }
	private:
		uint32_t m_RendererID;
		uint32_t m_ColorAttachment, m_DepthAttachment;
		FrambufferSpecification m_Specification;
	};

}