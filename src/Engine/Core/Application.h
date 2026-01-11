#pragma once
#include "Window.h"
#include "Graphics/Texture.h"
#include "Graphics/Camera.h"
#include "Core/Timestep.h"
#include "LayerStack.h"

#include <memory>
#include <iostream>
#include <glm/glm.hpp>



namespace Tassathras
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();


		static Application& get() { return *s_instance; }
		Tassathras::Window& getWindow() { return *m_window; }

	public:
		Application(const Application& other) = delete;
		Application& operator=(const Application& other) = delete;

		Application(Application&& other) noexcept = default;
		Application& operator=(Application&& other) noexcept = default;

		void pushLayer(Layer* layer);
		inline Camera& getCamera() { return *m_camera; }


	private:
		LayerStack m_layerStack;

		void init();
		void shutdown();
	private:
		std::unique_ptr<Tassathras::Window> m_window;
		bool m_running = true;
		static Application* s_instance;

		std::unique_ptr<Camera> m_camera;
		float m_lastFrameTime = 0.0f;

		std::shared_ptr<Texture> m_texture;

	};
}
