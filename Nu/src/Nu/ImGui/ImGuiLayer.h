#pragma once

#include "Nu/Core/Layer.h"

#include "Nu/Events/ApplicationEvent.h"
#include "Nu/Events/KeyEvent.h"
#include "Nu/Events/MouseEvent.h"

namespace Nu {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
	private:
		bool m_BlockEvents = true;
		float m_Time = 0.0f;
	};

}