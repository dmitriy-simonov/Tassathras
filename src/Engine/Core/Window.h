#pragma once
#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Tassathras
{
	struct WindowProps
	{
		std::string title;
		uint32_t w;
		uint32_t h;

		WindowProps(const std::string& t = "tassathras engi", uint32_t width = 1280, uint32_t height = 720)
			: title(t), w(width), h(height) { }
	};


	class Window
	{
	public:
		Window(const WindowProps& props);
		~Window();

		void onUpdate();
		bool shouldClose() const;


		uint32_t getWidth() const { return m_data.w; }
		uint32_t getHeight() const { return m_data.h; }
		GLFWwindow* getNativeWindow() const { return m_window; }

	private:
		void init(const WindowProps& props);
		void shutdown();

	private:
		GLFWwindow* m_window;
		
		struct WindowData
		{
			uint32_t w;
			uint32_t h;
			std::string title;
		};

		WindowData m_data;
	};
}