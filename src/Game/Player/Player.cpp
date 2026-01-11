#include "Player.h"

#include "Engine/Core/Input.h"
#include "Engine/Core/Timestep.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Graphics/Renderers/Renderer2D.h"

#include <GLFW/glfw3.h>

namespace GameTassathras
{
	Player::Player()
	{
		m_playerTexture = std::make_shared<Tassathras::Texture>("assets/textures/test2.png");
	}

	void Player::onUpdate(Tassathras::Timestep ts)
	{
		float speed = m_moveSpeed * ts;

		if (Tassathras::Input::isKeyPressed(GLFW_KEY_W)) m_position += speed;
		if (Tassathras::Input::isKeyPressed(GLFW_KEY_S)) m_position -= speed;
		if (Tassathras::Input::isKeyPressed(GLFW_KEY_A)) m_position -= speed;
		if (Tassathras::Input::isKeyPressed(GLFW_KEY_D)) m_position += speed;
	}

	void Player::onRender()
	{
		Tassathras::Renderer2D::drawQuad({ m_position.x, m_position.y }, { 0.6f, 0.6f }, m_playerTexture);
	}
}