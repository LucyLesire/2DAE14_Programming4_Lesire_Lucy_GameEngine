#pragma once
#include "Singleton.h"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(const std::string& name);
		std::shared_ptr<Scene> GetSceneAtIndex(int i) const { return m_Scenes[i]; };
		size_t GetAmountOfScenes() const { return m_Scenes.size(); };

		void Update(float dT);
		void Render();
		void FixedUpdate();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<std::shared_ptr<Scene>> m_Scenes;
	};
}
