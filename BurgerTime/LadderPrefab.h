#pragma once
#pragma warning(push, 0)
#include <memory>
#include <glm/glm.hpp>
#pragma warning (pop)

#include "Prefab.h"

namespace dae
{
	class CollisionComponent;
	class GameObject;

	class LadderPrefab : public Prefab
	{
	public:
		explicit LadderPrefab(glm::vec4 transformInfo, std::shared_ptr<GameObject> pGameObject);
		LadderPrefab() = default;
		~LadderPrefab() = default;
		LadderPrefab(const LadderPrefab& other) = delete;
		LadderPrefab(LadderPrefab&& other) noexcept = delete;
		LadderPrefab& operator=(const LadderPrefab& other) = delete;
		LadderPrefab& operator=(LadderPrefab&& other) noexcept = delete;
	};
}

