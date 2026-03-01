#include "Window.h"
#include "Log.h"
#include "Input.h"

namespace Tassathras
{
	Window::Window(const WindowProps& props)
	{
		init(props);
	}
	Window::~Window()
	{
		shutdown();
	}

	void Window::init(const WindowProps& props)
	{
		m_data.title = props.title;
		m_data.w = props.w;
		m_data.h = props.h;

		TS_CORE_INFO("create window {0} {1} {2}", props.title, props.w, props.h);

		if (!glfwInit())
		{
			TS_CORE_ERROR("not init glfw");
			return;
		}
		glfwSetErrorCallback([](int error, const char* description) {
			TS_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
			});
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		m_window = glfwCreateWindow(
			static_cast<int>(props.w), 
			static_cast<int>(props.h),
			m_data.title.c_str(), 
			nullptr, 
			nullptr);


		if (!m_window)
		{
			TS_CORE_ERROR("failed create glfw window");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(m_window);
		//Сюда ещё вернусь попозже, мог заюзать си-каст, но решил не делать, всё равно этот каст в итоге будет использовать реинтепрет
		//здесь приведение указателя на ф-ию, специфичное для API
		//В дальнейшем пересмотрю использование
		int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
		if (!status)
		{
			TS_CORE_INFO("failed init glad");
			return;
		}
		glfwSetWindowUserPointer(m_window, &m_data);
		glfwSwapInterval(1);


		//keyboard
		glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS)
				Input::setKeyPressed(static_cast<KeyCode>(key), true);
			else if (action == GLFW_RELEASE)
				Input::setKeyPressed(static_cast<KeyCode>(key), false);
		});

		//mouse buttons
		glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods) {
			if (action == GLFW_PRESS)
				Input::setMouseButtonPressed(static_cast<KeyCode>(button), true);
			else if (action == GLFW_RELEASE)
				Input::setMouseButtonPressed(static_cast<KeyCode>(button), false);
		});

		//mouse position
		glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xpos, double ypos) {
			Input::setMousePosition(static_cast<float>(xpos), static_cast<float>(ypos));
		});

		//mouse scroll
		glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xoffset, double yoffset) {
			Input::setScrollOffset(static_cast<float>(yoffset));
		});
	}

	void Window::onUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_window);
	}

	bool Window::shouldClose() const
	{
		return static_cast<bool>(glfwWindowShouldClose(m_window));
	}

	void Window::shutdown()
	{
		glfwDestroyWindow(m_window);
		glfwTerminate();
	}

}