#pragma once
#include <glm/glm.hpp>
#include <string>

namespace Game
{
	enum class TerrainType
	{
		Grass,
		Dirt,
		Sand,
		Water,
		Stone,
		COUNT
	};

	struct Tile
	{
		TerrainType terrain = TerrainType::Grass;
		bool isPassable = true;
		int height = 0;
		int textureVariant = 0;

		struct Resources
		{
			bool hasTree = false;
			bool hasStone = false;
			bool hasGold = false;
		} resources;

		bool canBuild() const
		{
			return isPassable &&
				   terrain != TerrainType::Water &&
				   height == 0 &&
				   !resources.hasTree &&
				   !resources.hasStone;
		}
	};

	struct TileTextures
	{
		static const char* getTexturePath(TerrainType type)
		{
			switch (type)
			{
			case Game::TerrainType::Grass: return "assets/tiles/grass.png";
			case Game::TerrainType::Dirt:  return "assets/tiles/dirt.png";
			case Game::TerrainType::Sand:  return "assets/tiles/sand.png";
			case Game::TerrainType::Water: return "assets/tiles/water.png";
			case Game::TerrainType::Stone: return "assets/tiles/stone.png";
			case Game::TerrainType::COUNT: return "assets/tiles/grass.png";
			default: return "assets/tiles/grass.png";
			}
		}
		
		static glm::vec4 getColor(TerrainType type)
		{
			switch (type)
			{
			case Game::TerrainType::Grass: return { 0.2f, 0.8f, 0.3f, 1.0f };
			case Game::TerrainType::Dirt:  return { 0.6f, 0.4f, 0.2f, 1.0f };
			case Game::TerrainType::Sand:  return { 0.9f, 0.8f, 0.5f, 1.0f };
			case Game::TerrainType::Water: return { 0.2f, 0.8f, 0.3f, 1.0f };
			case Game::TerrainType::Stone: return { 0.2f, 0.4f, 0.8f, 1.0f };
			case Game::TerrainType::COUNT: return { 0.5f, 0.5f, 0.5f, 1.0f };
			default: return {1.0f, 1.0f, 1.0f, 1.0f};
			}
		}
	};
}