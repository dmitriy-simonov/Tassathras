#include "Input.h"
#include <GLFW/glfw3.h>

namespace Tassathras
{
	std::array<bool, Input::MAX_KEYS> Input::s_keys = {};
	std::array<bool, Input::MAX_KEYS> Input::s_keyLastFrame = {};
	std::array<bool, Input::MAX_MOUSE_BUTTONS> Input::s_mouseButtons = {};
	std::array<bool, Input::MAX_MOUSE_BUTTONS> Input::s_mouseButtonsLastFrame = {};
	glm::vec2 Input::s_mousePos = { 0.0f, 0.0f };
	float Input::s_scrollOffset = 0.0f;
	float Input::s_scrollOffsetLastFrame = 0.0f;
	float Input::s_scrollY = 0.0f;

	void Input::transition()
	{
		s_keyLastFrame = s_keys;
		s_mouseButtonsLastFrame = s_mouseButtons;

		s_scrollOffsetLastFrame = s_scrollOffset;
		s_scrollOffset = 0.0f;

		s_scrollY = 0.0f;
	}

	void Input::clear()
	{
		s_keys.fill(false);
		s_keyLastFrame.fill(false);
		s_mouseButtons.fill(false);
		s_mouseButtonsLastFrame.fill(false);
		s_scrollOffset = 0.0f;
		s_scrollOffsetLastFrame = 0.0f;
		s_scrollY = 0.0f;
	}

	bool Input::isKeyPressed(KeyCode keycode)
	{
		return (keycode >= 0 && keycode < MAX_KEYS) ? s_keys[keycode] : false;
	}

	bool Input::isKeyJustPressed(KeyCode keycode)
	{
		return (keycode >= 0 && keycode < MAX_KEYS) ? (s_keys[keycode] && !s_keyLastFrame[keycode]) : false;
	}

	bool Input::isKeyReleased(KeyCode keycode)
	{
		return (keycode >= 0 && keycode < MAX_KEYS) ? (!s_keys[keycode] && s_keyLastFrame[keycode]) : false;
	}

	bool Input::isMouseButtonPressed(KeyCode button)
	{
		return (button >= 0 && button < MAX_MOUSE_BUTTONS) ? s_mouseButtons[button] : false;
	}

	bool Input::isMouseButtonJustPressed(KeyCode button)
	{
		return (button >= 0 && button < MAX_MOUSE_BUTTONS) ? (s_mouseButtons[button] && !s_mouseButtonsLastFrame[button]) : false;
	}

	bool Input::isMouseButtonReleased(KeyCode button)
	{
		return (button >= 0 && button < MAX_MOUSE_BUTTONS) ? (!s_mouseButtons[button] && s_mouseButtonsLastFrame[button]) : false;
	}

	glm::vec2 Input::getMousePosition()
	{
		return s_mousePos;
	}

	float Input::getMouseX()
	{
		return s_mousePos.x;
	}

	float Input::getMouseY()
	{
		return s_mousePos.y;
	}

	float Input::getScrollY()
	{
		return s_scrollOffsetLastFrame;
	}

	float Input::getScrollDelta()
	{
		return s_scrollY;
	}

	void Input::setKeyPressed(KeyCode keycode, bool isPressed)
	{
		if (keycode >= 0 && keycode < MAX_KEYS) s_keys[keycode] = isPressed;
	}

	void Input::setMouseButtonPressed(KeyCode button, bool isPressed)
	{
		if (button >= 0 && button < MAX_MOUSE_BUTTONS) s_mouseButtons[button] = isPressed;
	}

	void Input::setMousePosition(float x, float y)
	{
		s_mousePos = { x, y };
	}

	void Input::setScrollOffset(float offset)
	{
		s_scrollOffset = offset;
		s_scrollY += offset; 
	}
}