#pragma once
#include "Singleton.h"
#include <vector>
#include <memory>
#include <iostream>

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::shared_ptr<Scene>& scene);
		std::shared_ptr<Scene> GetSceneAtIndex(int i) const { return m_Scenes[i]; };
		size_t GetAmountOfScenes() const { return m_Scenes.size(); };

		void Initialize();
		void Update(float dT);
		void Render();
		void FixedUpdate(float fDT);
		void LateUpdate(float dT);

		void SetActiveScene(std::shared_ptr<Scene> scene);
		void RestartScene();

		void RestartSceneAtEndGameLoop();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;

		std::shared_ptr<Scene> m_ActiveScene{};
		bool m_RestartScene{};
	};
}
