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
		if (s_instance != nullptr)
		{
			std::cerr << "application already exissts\n";
			return;
		}
		s_instance = this;
		init();
	}

	Application::~Application()
	{
		shutdown();
		s_instance = nullptr;
	}
	//===============================================================
	// life cycle
	//===============================================================
	void Application::init()
	{
		m_window = std::make_unique<Tassathras::Window>(Tassathras::WindowProps());

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		Renderer2D::init();
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		float aspectRatio = (float)m_window->getWidth() / (float)m_window->getHeight();
		m_camera = std::make_unique<Camera>(-aspectRatio, aspectRatio, -1.0f, 1.0f);
		

		m_texture = std::make_shared<Texture>("assets/textures/test.png");
	}

	void Application::shutdown()
	{
		Renderer2D::shutdown();
		glfwTerminate();
	}
	void Application::run()
	{
		while (!m_window->isClosed() && m_running)
		{
			float time = (float)glfwGetTime();
			Timestep ts = time - m_lastFrameTime;
			m_lastFrameTime = time;

			glm::vec3 camPos = m_camera->getPosition();
			float camSpeed = 3.0f * ts;

			if (Input::isKeyPressed(GLFW_KEY_W))
			{
				camPos.y += camSpeed;
				std::cout << camPos.y << " W pressed!" << std::endl;
			}
			if (Input::isKeyPressed(GLFW_KEY_S))
			{
				camPos.y -= camSpeed;
				std::cout << camPos.y << " S pressed!" << std::endl;
			}
			if (Input::isKeyPressed(GLFW_KEY_A))
			{
				camPos.x -= camSpeed;
				std::cout << camPos.x << " A pressed!" << std::endl;
			}
			if (Input::isKeyPressed(GLFW_KEY_D))
			{
				camPos.x += camSpeed;
				std::cout << camPos.x << " D pressed!" << std::endl;
			}


			m_camera->setPosition(camPos);

;
			if (Input::isMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT))
			{
				auto mousePos = Input::getMousePosition();
				std::cout << "left click at: " << mousePos.x << ", " << mousePos.y << std::endl;
			}
			
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT); // for clear color;


			Renderer2D::beginScene(m_camera->getViewProjectionMatrix());
			//Renderer2D::drawQuad({ -1.0f, 0.0f }, { 0.3f, 0.3f }, { 0.0f, 0.0f, 1.0f, 1.0f });
			Renderer2D::drawQuad({ 0.0f, 0.0f }, { 0.5f, 0.5f }, m_texture);
			Renderer2D::drawQuad({ 1.0f, 1.0f }, { 0.4f, 0.4f }, { 0.8f, 0.2f, 0.2f, 1.0f });

			Renderer2D::endScene();

			m_window->onUpdate();
			Input::update();
		}
	}

}