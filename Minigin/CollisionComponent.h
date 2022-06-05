#pragma once

#include "BaseComponent.h"
#include "Transform.h"

namespace dae
{
	struct Box2D
	{
		Box2D() = default;
		explicit Box2D(const Transform2D& bottomLeft, const Transform2D& size)
		{
			m_BottomLeft = bottomLeft;
			m_Size = size;
		}

		Transform2D m_BottomLeft{};
		Transform2D m_Size{};
	};

	class CollisionComponent : public BaseComponent
	{
	public:
		CollisionComponent(GameObject* pOwner, bool active, float width, float height, bool centered = true);
		~CollisionComponent() = default;
		CollisionComponent(const CollisionComponent& other) = delete;
		CollisionComponent(CollisionComponent&& other) noexcept = delete;
		CollisionComponent& operator=(const CollisionComponent& other) = delete;
		CollisionComponent& operator=(CollisionComponent&& other) noexcept = delete;

		void Initialize() override;
		void FixedUpdate(float) override {};
		void Update(float dT) override;
		void LateUpdate(float) override{};

		const Box2D GetCollisionBox2D() const { return m_ColBox2D; }

		bool CollideCheck(CollisionComponent* pCollider) const;

		bool IsActive() const { return m_Active; }
		void SetAtive(bool active) { m_Active = active; }

		bool IsColliding() const { return m_Colliding; }
		void SetColliding(bool enable) { m_Colliding = enable; }
	private:
		Box2D m_ColBox2D;
		bool m_Active;
		float m_Width;
		float m_Height;

		bool m_Centered{};
		bool m_Colliding{};
	};
}



