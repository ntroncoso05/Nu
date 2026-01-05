#pragma once

namespace Nu {

	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class Renderer
	{
	public:
		inline static RendererAPI GetApi() /*const*/ { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};
}