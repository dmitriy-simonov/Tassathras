#pragma once
#include "Engine/Core/Application.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/Buffers/VertexArray.h"
#include "Engine/Graphics/Texture.h"
#include "Engine/Graphics/IsometricCamera.h"
#include <memory>

struct Tile
{
	int type = 0; // 0 - water 1 y
};

class Game : public Tassathras::Application
{

public:
	Game();
	virtual ~Game() = default;

	void onStart() override;
	void onUpdate(float dt) override;
	void onRender() override;

	void onMouseClick(float mouseX, float mouseY);

private:
	void renderDebugGrid(const Tassathras::IsometricCamera::Bounds& bounds);
	void renderIsland(int centerX, int centerY, int size, float baseHeight = 0.0f);

	bool tileExists(int x, int y) const;

	float getTileHeight(int x, int y) const;

	std::shared_ptr<Tassathras::Texture2D> selectTileTexture(int x, int y, float height) const;

	void renderCanvasBorder();
	void renderDebugGrid();

private:
	std::shared_ptr<Tassathras::Texture2D> m_backgroundTexture;
	std::shared_ptr<Tassathras::Texture2D> m_tileTexture;      
	std::shared_ptr<Tassathras::Texture2D> m_grassTexture;
	std::shared_ptr<Tassathras::Texture2D> m_dirtTexture;
	std::shared_ptr<Tassathras::Texture2D> m_sandTexture;

	std::unique_ptr<Tassathras::IsometricCamera> m_camera;

	float m_tileWidth = 128.0f;
	float m_tileHeight = 64.0f;

	bool m_showDebugGrid = false;
	int m_selectedTileX = 999999;
	int m_selectedTileY = 999999;

	glm::vec2 m_cameraVelocity{ 0.0f, 0.0f };
	float m_cameraFriction = 10.0f;
	float m_cameraAcceleration = 100.0f;

	bool m_isDragging = false;
	glm::vec2 m_lastMousePos{ 0.0f, 0.0f };
	float m_dragSensitivity = 1.5f;


public:
	enum class GameState
	{
		MainMenu,
		Editor
	};

private:
	GameState m_state = GameState::MainMenu;

	std::vector<Tile> m_mapData;

	int m_mapWidth;
	int m_mapHeight;
	int m_brushType;

	const int MAP_SIZE_TINY = 16;
	const int MAP_SIZE_SMALL = 32;
	const int MAP_SIZE_MEDIUM = 64;
	const int MAP_SIZE_LARGE = 128;
	const int MAP_SIZE_HUGE = 256;

	void initMap(int size);
};