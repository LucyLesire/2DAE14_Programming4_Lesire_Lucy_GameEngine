#pragma once
#include "Scene.h"

namespace dae
{
	class BurgerTimeMenu : public Scene
	{
	public:
		BurgerTimeMenu(const std::string& name, uint32_t width, uint32_t height, unsigned int id);
		~BurgerTimeMenu() override = default;
		BurgerTimeMenu(const BurgerTimeMenu& other) = delete;
		BurgerTimeMenu(BurgerTimeMenu&& other) noexcept = delete;
		BurgerTimeMenu& operator=(const BurgerTimeMenu& other) = delete;
		BurgerTimeMenu& operator=(BurgerTimeMenu&& other) noexcept = delete;

		void Initialize() override;

	private:
		void ReadHighScores();
		void UpdateHighScores(unsigned int score);
	};

}

