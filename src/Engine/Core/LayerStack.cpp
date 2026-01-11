#include "LayerStack.h"

namespace Tassathras
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_layers)
		{
			layer->onDetach();
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer)
	{
		m_layers.emplace_back(layer);
	}
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end())
		{
			layer->onDetach();
			m_layers.erase(it);
		}
	}
}