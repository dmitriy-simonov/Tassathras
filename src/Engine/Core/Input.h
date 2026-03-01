#pragma once
#include "KeyCodes.h"
#include <glm/glm.hpp>
#include <array>

namespace Tassathras
{
	class Input
	{
	public:
		static bool isKeyPressed(KeyCode keycode);
		static bool isKeyJustPressed(KeyCode keycode);
		static bool isKeyReleased(KeyCode keycode);

		static bool isMouseButtonPressed(KeyCode button);
		static bool isMouseButtonJustPressed(KeyCode button);
		static bool isMouseButtonReleased(KeyCode button); 

		static glm::vec2 getMousePosition();
		static float getMouseX();
		static float getMouseY();

		static float getScrollY();
		static float getScrollDelta(); 

		static void transition();
		static void clear();

		static void setKeyPressed(KeyCode keycode, bool isPressed);
		static void setMouseButtonPressed(KeyCode button, bool isPressed);
		static void setMousePosition(float x, float y);
		static void setScrollOffset(float offset);

	private:
		static constexpr size_t MAX_KEYS = 512;
		static constexpr size_t MAX_MOUSE_BUTTONS = 8;

		static std::array<bool, MAX_KEYS> s_keys;
		static std::array<bool, MAX_KEYS> s_keyLastFrame;

		static std::array<bool, MAX_MOUSE_BUTTONS> s_mouseButtons;
		static std::array<bool, MAX_MOUSE_BUTTONS> s_mouseButtonsLastFrame;

		static glm::vec2 s_mousePos;
		static float s_scrollOffset;
		static float s_scrollOffsetLastFrame;

		static float s_scrollY; 

	private:
		Input() = delete;
	};
}