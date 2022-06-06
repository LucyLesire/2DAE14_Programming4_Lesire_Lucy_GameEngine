#pragma once
#include "Singleton.h"

class GameInstance final : public dae::Singleton<GameInstance>
{
public:
	GameInstance() = default;
	~GameInstance() override = default;
	GameInstance(const GameInstance& other) = delete;
	GameInstance(GameInstance&& other) noexcept = delete;
	GameInstance& operator=(const GameInstance& other) = delete;
	GameInstance& operator=(GameInstance&& other) noexcept = delete;

	void Init(unsigned int maxBugers);

	void AddBurgersDropped() { m_BurgersDropped++; }
	void Reset() { m_BurgersDropped = 0; }
	bool GetAllBurgersDropped() { return m_BurgersDropped == m_MaxBurgersDropped; }

private:
	unsigned int m_BurgersDropped{ 0 };
	unsigned int m_MaxBurgersDropped{ 4 };
};

