#pragma once
#include "Window.h"
#include <memory>

namespace Tassathras
{
	class Application
	{
	public:
		Application();
		virtual ~Application();

		void run();
		void stop();

		virtual void onStart() {}
		virtual void onUpdate(float dt) {}
		virtual void onRender() {}

		static Application& get() { return *s_instance; }
		Window& getWindow() { return *m_window; }

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;

		static Application* s_instance;
	};

	Application* createApplication();
}