#pragma once
#include <memory>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

namespace dae
{
	class GameObject;
	class CollisionComponent;

	class Prefab
	{
	public:
		Prefab(glm::vec4 transformInfo, std::shared_ptr<GameObject> pGameObject);
		~Prefab() = default;
		Prefab(const Prefab& other) = delete;
		Prefab(Prefab&& other) noexcept = delete;
		Prefab& operator=(const Prefab& other) = delete;
		Prefab& operator=(Prefab&& other) noexcept = delete;

		std::shared_ptr<CollisionComponent> GetColComp() const { return m_pCol; }
		std::shared_ptr<GameObject> GetObject() const { return m_pGameObject; }

		void Initialize();
	private:
		glm::vec4 m_TransformInformation{};
		std::shared_ptr<CollisionComponent> m_pCol{};
		std::shared_ptr<GameObject> m_pGameObject{};
	};
}


