#include "TileManager.h"

TileManager::~TileManager()
{
    for(unsigned int i{}; i < m_Tiles.size(); ++i)
    {
        delete m_Tiles[i];
        m_Tiles[i] = nullptr;
    }
}

void TileManager::InitializeTiles(const std::vector<Tile*>& tiles, int rows, int cols, int windowHeight, int windowWidth)
{
    for (unsigned int i{}; i < m_Tiles.size(); ++i)
    {
        delete m_Tiles[i];
        m_Tiles[i] = nullptr;
    }

    m_WindowWidth = windowWidth;
    m_WindowHeight = windowHeight;
	m_Tiles = tiles;
	m_NrOfRows = rows;
	m_NrOfCols = cols;
}

int TileManager::PositionToIndex(const glm::vec2& pos) const
{
    //Check if position is inside window
    if (pos.x >= 0.f && pos.y >= 0.f && pos.x < m_WindowWidth && pos.y < m_WindowHeight)
    {
        const int indexX = static_cast<int>(pos.x / m_WindowWidth * m_NrOfCols);
        const int indexY = static_cast<int>(pos.y / m_WindowHeight * m_NrOfRows);

       return indexX * m_NrOfRows + (indexY);
    }
    return 0;
}

glm::vec2 TileManager::IndexToPosition(unsigned int index) const
{
    //Get pos from index
    if (index < m_Tiles.size() && index >= 0)
    {
        glm::vec2 pos{};
        int indexX = index % m_NrOfCols;
        int indexY = index / m_NrOfRows;

        pos.x = static_cast<float>(indexX * m_WindowWidth / m_NrOfCols);
        pos.y = static_cast<float>(indexY * m_WindowHeight / m_NrOfRows);

        return pos;
    }
    return { 0.f, 0.f };
}

void TileManager::SetTileType(TileType type, int index) const
{
    m_Tiles[index]->m_Type = type;
}

void TileManager::SetExtraTileType(ExtraType type, int index) const
{
    m_Tiles[index]->m_ExtraType = type;
}
