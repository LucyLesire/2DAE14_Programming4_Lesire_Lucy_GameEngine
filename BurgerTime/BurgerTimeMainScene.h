#pragma once
#include <string>

#include "Scene.h"

namespace  dae
{
	class SDLSoundSystem;
	class Prefab;

	class BurgerTimeMainScene : public dae::Scene
	{
	public:
		BurgerTimeMainScene(const std::string& name, uint32_t width, uint32_t height, unsigned int id, const std::string& levelFile);
		~BurgerTimeMainScene() override = default;
		BurgerTimeMainScene(const BurgerTimeMainScene& other) = delete;
		BurgerTimeMainScene(BurgerTimeMainScene&& other) noexcept = delete;
		BurgerTimeMainScene& operator=(const BurgerTimeMainScene& other) = delete;
		BurgerTimeMainScene& operator=(BurgerTimeMainScene&& other) noexcept = delete;

		void Initialize() override;
		void Update(float dT) override;

	private:
		void ReadJson(const std::string& fileLoc);

		std::shared_ptr<SDLSoundSystem> m_pSoundSystem{};

		std::string m_LevelFile{};

		int m_Rows{};
	};
}


