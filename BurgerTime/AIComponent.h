#pragma once
#include "BaseComponent.h"

struct Tile;

namespace dae
{
	class AIComponent : public dae::BaseComponent
	{
	public:
		AIComponent(GameObject* pOwner, GameObject* pPlayer, float speed = 100.f);
		~AIComponent() override = default;
		AIComponent(const AIComponent& other) = delete;
		AIComponent(AIComponent&& other) noexcept = delete;
		AIComponent& operator=(const AIComponent& other) = delete;
		AIComponent& operator=(AIComponent&& other) noexcept = delete;

		void FixedUpdate(float) override {};
		void Update(float dT) override;
		void Initialize() override {};
		void LateUpdate(float) override {};

		bool GetSquished() const { return m_Squished; }

		void ResetStunned(float dt);
		bool GetStunned() const { return m_Stunned; }
	private:
		GameObject* m_pPlayer;
		float m_Speed{};
		std::vector<Tile*> m_pPath{};

		void CalculatePath(const Transform& toPos);
		void Squished(float dT);

		bool m_Stuck{};
		Transform m_GetOutOfStuck{};

		bool m_Squished{};

		float m_SquishedTime{};
		float m_MaxSquishedTime{ 1.f };

		float m_StunnedTime{};
		float m_MaxStunnedTime{2.f};

		bool m_Stunned{};
	};
}


