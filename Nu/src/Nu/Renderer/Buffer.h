#pragma once

namespace Nu {
	// Pure virtual interfaces

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static VertexBuffer* Create(float* vertices, uint32_t size); // kinda the constructor, could use usize_t instead of uint32_t
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() {}

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual uint32_t GetCount() const = 0;

		static IndexBuffer* Create(uint32_t* indices, uint32_t size); // kinda the constructor
		// using 32 bits int, could change to 16 bits as an optimization but probably could run out of indices
	};
}