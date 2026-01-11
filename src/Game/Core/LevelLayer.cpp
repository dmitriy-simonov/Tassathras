#include "LevelLayer.h"
#include "Components.h"
#include "Engine/Core/Input.h"
#include "Engine/Graphics/Renderers/Renderer2D.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Game
{
	LevelLayer::LevelLayer()
		: Layer("llv"),
		m_camera(-1.6f, 1.6f, -0.9f, 0.9f)
	{

	}

	void LevelLayer::onAttach()
	{
		m_player = m_registry.create();


		m_registry.emplace<TransformComponent>(m_player, TransformComponent{ {0.0f, 0.0f}, {1.0f, 1.0f} });

		auto texture = std::make_shared<Tassathras::Texture>("assets/textures/test2.png");

		m_registry.emplace<SpriteComponent>(m_player, SpriteComponent{ {1.0f, 1.0f, 1.0f, 1.0f}, texture });
		m_registry.emplace<PlayerControllerComponent>(m_player, PlayerControllerComponent{ 2.5f });

		auto tree = m_registry.create();

		m_registry.emplace<TransformComponent>(tree, TransformComponent{ {0.5f,0.5f},{0.5f, 0.5f} });
		m_registry.emplace<SpriteComponent>(tree, SpriteComponent{ {1.0f, 0.0f, 0.0f, 1.0f}, texture});
	}

	void LevelLayer::onUpdate(Tassathras::Timestep ts)
	{
		auto view = m_registry.view<TransformComponent, PlayerControllerComponent>();
		 view.each([&](auto entity, auto& transform, auto& controller)
			{
				 glm::vec2 move(0.0f);

				 if (Tassathras::Input::isKeyPressed(GLFW_KEY_W)) { move.y += 1.0f;}
				 if (Tassathras::Input::isKeyPressed(GLFW_KEY_S)) { move.y -= 1.0f;}
				 if (Tassathras::Input::isKeyPressed(GLFW_KEY_A)) { move.x -= 1.0f;}
				 if (Tassathras::Input::isKeyPressed(GLFW_KEY_D)) { move.x += 1.0f;}


				 if (glm::length(move) > 0.0f)
				 {
					 move = glm::normalize(move);
					 transform.m_translation += move * controller.m_speed * (float)ts;
					 std::cout << "POS: " << transform.m_translation.x << ", " << transform.m_translation.y << '\n';
				 }

			});

		 auto playerTransform = m_registry.get<TransformComponent>(m_player);
		 m_camera.setPosition({ playerTransform.m_translation.x, playerTransform.m_translation.y, 0.0f });
	}

	void LevelLayer::onRender()
	{

		auto view = m_registry.view<TransformComponent, SpriteComponent>();

		Tassathras::Renderer2D::beginScene(m_camera.getViewProjectionMatrix());


		view.each([](auto& transform, auto& sprite) {
			Tassathras::Renderer2D::drawQuad(transform.m_translation, transform.m_scale, sprite.texture);
			});

		Tassathras::Renderer2D::endScene();
		
	}
}