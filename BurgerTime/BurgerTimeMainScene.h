#pragma once
#include <string>

#include "Scene.h"

namespace  dae
{
	class SDLSoundSystem;
	class Prefab;
	class LadderPrefab;

	class BurgerTimeMainScene : public dae::Scene
	{
	public:
		BurgerTimeMainScene(const std::string& name);
		~BurgerTimeMainScene() = default;
		BurgerTimeMainScene(const BurgerTimeMainScene& other) = delete;
		BurgerTimeMainScene(BurgerTimeMainScene&& other) noexcept = delete;
		BurgerTimeMainScene& operator=(const BurgerTimeMainScene& other) = delete;
		BurgerTimeMainScene& operator=(BurgerTimeMainScene&& other) noexcept = delete;

		void Initialize() override;

	private:
		void ReadJson(const std::wstring& fileLoc);

		std::vector<std::shared_ptr<Prefab>> m_pPrefabs{};

		std::shared_ptr<SDLSoundSystem> m_pSoundSystem{};
	};
}


