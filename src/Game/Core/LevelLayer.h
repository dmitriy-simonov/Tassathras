#pragma once

#include "Core/Layer.h" 
#include "Engine/Graphics/Camera.h"
#include <entt/entt.hpp>

namespace Game
{
	class LevelLayer : public Tassathras::Layer
	{
	public:
		LevelLayer();
		virtual ~LevelLayer() = default;
		virtual void onAttach() override;
		virtual void onUpdate(Tassathras::Timestep ts) override;
		virtual void onRender() override;

	private:
		Tassathras::Camera m_camera;
		entt::registry m_registry;
		entt::entity m_player = entt::null;
	};
}
