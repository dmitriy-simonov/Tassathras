#pragma once
#include <glm/glm.hpp>
namespace Tassathras
{
	class Camera
	{
	public:
		Camera(float left, float right, float bottom, float top);

		void setPosition(const glm::vec3& pos) { m_position = pos; updateMetrices(); };
		const glm::vec3& getPosition() const { return m_position; }

		void setRotation(float rotation) { m_rotation = rotation; updateMetrices(); }
		float getRotation() const { return m_rotation; }

		const glm::mat4& getProjectionMatrix() const { return m_projectionMatrix; }
		const glm::mat4& getViewMatrix() const { return m_viewMatrix; }
		const glm::mat4& getViewProjectionMatrix() const { return m_viewProjectionMatrix; }

	private:
		void updateMetrices();
	private:
		glm::mat4 m_projectionMatrix;
		glm::mat4 m_viewMatrix;
		glm::mat4 m_viewProjectionMatrix;

		glm::vec3 m_position = { 0.0f, 0.0f, 0.0f };
		float m_rotation = 0.0f;
	};
}