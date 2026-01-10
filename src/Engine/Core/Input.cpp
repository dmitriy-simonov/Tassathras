#include "Input.h"
#include <GLFW/glfw3.h>

namespace Tassathras
{
	std::array<bool, Input::MAX_KEYS> Input::m_keys = {};
	std::array<bool, Input::MAX_KEYS> Input::m_keyLastFrame = {};
	std::array<bool, Input::MAX_MOUSE_BUTTONS> Input::m_mouseButtons = {};
	std::array<bool, Input::MAX_MOUSE_BUTTONS> Input::m_mouseButtonsLastFrame = {};
	glm::vec2 Input::m_mousePos = { 0.0f, 0.0f };

	void Input::update()
	{
		m_keyLastFrame = m_keys;
		m_mouseButtonsLastFrame = m_mouseButtons;
	}

	bool Input::isKeyPressed(int keycode)
	{
		return m_keys[keycode];
	}

	bool Input::isKeyJustPressed(int keycode)
	{
		return m_keys[keycode] && !m_keyLastFrame[keycode];
	}


	bool Input::isMouseButtonPressed(int button)
	{
		return m_mouseButtons[button];
	}

	bool Input::isMouseButtonJustPressed(int button)
	{
		return m_mouseButtons[button] && !m_mouseButtonsLastFrame[button];
	}

	glm::vec2 Input::getMousePosition()
	{
		return m_mousePos;
	}

	void Input::setKeyPressed(int keycode, bool isPressed)
	{
		if (keycode >= 0 && keycode < MAX_KEYS) m_keys[keycode] = isPressed;
	}
	void Input::setMouseButtonPressed(int button, bool isPressed)
	{
		if (button >= 0 && button < MAX_MOUSE_BUTTONS) m_mouseButtons[button] = isPressed;
	}

	void Input::setMousePosition(float x, float y)
	{
		m_mousePos = { x, y };
	}
}