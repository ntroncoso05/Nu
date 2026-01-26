#pragma once

#include "Nu/Core/Layer.h"

#include "Nu/Events/ApplicationEvent.h"
#include "Nu/Events/KeyEvent.h"
#include "Nu/Events/MouseEvent.h"

namespace Nu {

	class NU_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};

}