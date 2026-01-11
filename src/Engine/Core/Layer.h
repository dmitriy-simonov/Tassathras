#pragma once
#include "Core/Timestep.h"
#include <string>

namespace Tassathras
{
	class Layer
	{
	public:
		Layer(const std::string& name = "Layer") : m_debugName(name) {}
		virtual ~Layer() = default;

		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate(Timestep ts) {}
		virtual void onRender() {}

		inline const std::string& getName() const { return m_debugName; }
	protected:
		std::string m_debugName;
	};
}
