#pragma once
namespace dae
{
	class CollisionComponent;
	class CollisionManager
	{
	public:
		CollisionManager() = default;
		~CollisionManager() = default;
		CollisionManager(const CollisionManager& other) = delete;
		CollisionManager(CollisionManager&& other) noexcept = delete;
		CollisionManager& operator=(const CollisionManager& other) = delete;
		CollisionManager& operator=(CollisionManager&& other) noexcept = delete;

		void Update(float dt);

		void AddCollider(dae::CollisionComponent* pCollider);

	private:
		std::vector<CollisionComponent*> m_pColliders{};
	};
}



