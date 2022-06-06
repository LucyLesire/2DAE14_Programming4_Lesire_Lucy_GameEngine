#pragma once
#include <string>

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
	void Reset() { m_BurgersDropped = 0;}
	void FullReset() { m_BurgersDropped = 0; m_Lives = 3; m_Score = 0; };
	bool GetAllBurgersDropped() const { return m_BurgersDropped == m_MaxBurgersDropped; }

	void LostLife() { m_Lives--; }
	unsigned int GetLives() const { return m_Lives; };

	void SetScore(unsigned int score) { m_Score = score; }
	unsigned int GetScore() const { return m_Score; }

	std::string GetPlayer() const { return m_Player; }
	void SetPlayer(const std::string& player) { m_Player = player; }

private:
	unsigned int m_BurgersDropped{ 0 };
	unsigned int m_MaxBurgersDropped{ 4 };

	unsigned int m_Lives{ 3 };

	unsigned int m_Score{0};

	std::string m_Player{};
};

