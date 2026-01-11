#include "Application.h"
#include "Graphics/Renderers/Renderer2D.h"
#include "Input.h"
#include "Graphics/Texture.h"
#include "Timestep.h"


#include<GLFW/glfw3.h>
#include<glm/gtc/matrix_transform.hpp>



namespace Tassathras
{
	
	Application* Application::s_instance = nullptr;

	Application::Application()
	{
		s_instance = this;
		init();
	}

	Application::~Application()
	{
		shutdown();
	}
	//===============================================================
	// life cycle
	//===============================================================
	void Application::init()
	{
		m_window = std::make_unique<Tassathras::Window>(Tassathras::WindowProps());

		Renderer2D::init();
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float aspectRatio = (float)m_window->getWidth() / (float)m_window->getHeight();
		m_camera = std::make_unique<Camera>(-aspectRatio, aspectRatio, -1.0f, 1.0f);
		
	
	}

	void Application::shutdown()
	{
		Renderer2D::shutdown();
		glfwTerminate();
	}

	void Application::pushLayer(Layer* layer)
	{
		m_layerStack.pushLayer(layer);
		layer->onAttach();
	}

	void Application::run()
	{
		while (!m_window->isClosed() && m_running)
		{
			float time = (float)glfwGetTime();
			Timestep ts = time - m_lastFrameTime;
			m_lastFrameTime = time;


			for (Layer* layer : m_layerStack)
				layer->onUpdate(ts);

			
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT); // for clear color;


			Renderer2D::beginScene(m_camera->getViewProjectionMatrix());
		
			for (Layer* layer : m_layerStack)
				layer->onRender();

			Renderer2D::endScene();

			m_window->onUpdate();
			Input::update();
		}
	}

}