#pragma once
#include <cstdint>
#include "BaseGame.h"

namespace dae
{
	class BurgerTimeGame final : public dae::BaseGame
	{
	public:
		BurgerTimeGame(uint32_t windowWidth = 748, uint32_t windowHeight = 720);
		~BurgerTimeGame() = default;
		BurgerTimeGame(const BurgerTimeGame& other) = delete;
		BurgerTimeGame(BurgerTimeGame&& other) noexcept = delete;
		BurgerTimeGame& operator=(const BurgerTimeGame& other) = delete;
		BurgerTimeGame& operator=(BurgerTimeGame&& other) noexcept = delete;

		void CreateGameScenes() override;
	};
}



