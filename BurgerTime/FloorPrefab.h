#pragma once
#pragma warning(push, 0)
#include <memory>
#include <glm/glm.hpp>

#include "Prefab.h"
#pragma warning (pop)

namespace dae
{
	class CollisionComponent;
	class GameObject;

	class FloorPrefab : public Prefab
	{
	public:
		explicit FloorPrefab(glm::vec4 transformInfo, std::shared_ptr<GameObject> pGameObject);
		FloorPrefab() = default;
		~FloorPrefab() = default;
		FloorPrefab(const FloorPrefab& other) = delete;
		FloorPrefab(FloorPrefab&& other) noexcept = delete;
		FloorPrefab& operator=(const FloorPrefab& other) = delete;
		FloorPrefab& operator=(FloorPrefab&& other) noexcept = delete;
	};
}

