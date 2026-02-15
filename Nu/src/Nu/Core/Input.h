#pragma once

#include <glm/glm.hpp>
#include "Nu/Core/KeyCodes.h"
#include "Nu/Core/MouseCodes.h"

namespace Nu {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};

}