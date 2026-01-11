#pragma once

#include <glm/glm.hpp>
#include <memory>
namespace Tassathras
{
	class Texture;
	class Timestep;
}

namespace GameTassathras
{
	class Player
	{
	public:
		Player();
		~Player() = default;

		void onUpdate(Tassathras::Timestep ts);
		void onRender();

		const glm::vec3& getPosition() const { return m_position; }

	private:
		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_moveSpeed = 4.0f;
		std::shared_ptr<Tassathras::Texture> m_playerTexture;
	};
}