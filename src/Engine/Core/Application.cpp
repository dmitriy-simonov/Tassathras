#include "Application.h"
#include "Log.h"
#include "Input.h"
#include <GLFW/glfw3.h>
#include <iostream>

namespace Tassathras
{
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		s_instance = this;
		Log::init();
		m_window = std::make_unique<Window>(WindowProps());
	}

	Application::~Application()
	{
		TS_CORE_INFO("engine shutdown");
	}

	void Application::run()
	{
		onStart();

		float lastFrameTime = 0.0f;
		int frameCount = 0;

		while (m_running && !m_window->shouldClose())
		{
			float time = static_cast<float>(glfwGetTime());
			float dt = time - lastFrameTime;
			lastFrameTime = time;
			if (dt > 0.1f) dt = 0.1f;
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			onUpdate(dt);
			onRender();
			Tassathras::Input::transition();

			m_window->onUpdate();

		}
	}

	void Application::stop()
	{

		m_running = false;
	}
}
