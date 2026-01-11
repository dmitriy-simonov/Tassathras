#pragma once
#include "Engine/Graphics/Texture.h"
#include <glm/glm.hpp>
#include <memory>

namespace Game
{
	struct TransformComponent
	{
		glm::vec2 m_translation = { 0.0f, 0.0f };
		glm::vec2 m_scale = { 1.0f, 1.0f };
	};

	struct SpriteComponent
	{
		glm::vec4 m_color = { 1.0f, 1.0f, 1.0f, 1.0f };
		std::shared_ptr<Tassathras::Texture> texture;

	};

	struct CameraComponent
	{
		float m_zoom = 1.0f;
		bool m_primary = true;
	};

	struct PlayerControllerComponent
	{
		float m_speed = 5.0f;
	};
}