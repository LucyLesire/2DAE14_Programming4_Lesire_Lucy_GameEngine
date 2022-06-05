#pragma once
#include "Singleton.h"
#pragma warning(push, 0)
#include <memory>
#include <vector>
#include <glm/glm.hpp>
#pragma warning (pop)

enum class TileType
{
	Empty,
	Floor,
	Ladder,
	Bun,
	Tray
};

enum class ExtraType
{
	Empty,
	TopBun,
	Cheese,
	Lettuce,
	Burger,
	Tomato,
	BottomBun
};

struct Tile
{
	glm::vec4 m_Boundingbox;
	bool m_IsTriggered;
	bool m_IsActive;
	TileType m_Type;
	ExtraType m_ExtraType;
	int m_Index;
	bool m_Pushed{};
	bool m_Falling{};

	Tile(glm::vec4 boundingBox, bool isActive, int index)
	{
		m_Boundingbox = boundingBox;
		m_IsActive = isActive;
		m_IsTriggered = false;
		m_Type = TileType::Empty;
		m_ExtraType = ExtraType::Empty;
		m_Index = index;
		m_Falling = false;
	}

	
};

class TileManager : public dae::Singleton<TileManager>
{
public:
	virtual ~TileManager() override;
	TileManager(const TileManager& other) = delete;
	TileManager(TileManager&& other) = delete;
	TileManager& operator=(const TileManager& other) = delete;
	TileManager& operator=(TileManager&& other) = delete;

	void InitializeTiles(const std::vector<Tile*>& tiles, int rows, int cols, int windowHeight, int windowWidth);

	Tile* GetTileAtPosition(const glm::vec2& pos) { return m_Tiles[PositionToIndex(pos)]; }
	Tile* GetTileAtIndex(int index) { return m_Tiles[index]; }

	int PositionToIndex(const glm::vec2& pos) const;
	glm::vec2 IndexToPosition(int index) const;

	void SetTileType(TileType type, int index);
	void SetExtraTileType(ExtraType type, int index);

	Tile* GetTileUnder(int index) { return m_Tiles[index + 1]; };

	float GetTileWidth() const { return m_TileWidth; }
	void SetTileWidth(float w) { m_TileWidth = w; }
private:
	friend class Singleton;
	TileManager() = default;

	int m_NrOfRows{};
	int m_NrOfCols{};
	std::vector<Tile*> m_Tiles{};

	int m_WindowHeight{};
	int m_WindowWidth{};

	float m_TileWidth{};
};

