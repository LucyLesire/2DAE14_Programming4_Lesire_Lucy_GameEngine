#pragma once
#include <SDL_rect.h>

#include "BaseComponent.h"
#include "PetterPepperComponent.h"

namespace dae
{
	class Subject;
	class EnemyComponent final : public BaseComponent
	{
	public:
		void Update(float dT) override;
		void FixedUpdate(float) override{};
		void Initialize() override {};
		void LateUpdate(float) override {};

		EnemyComponent(GameObject* pOwner, int score, GameObject* pPlayer);
		virtual ~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) = delete;

		void SetAnimState(AnimationState newState) { m_AnimState = newState; m_AnimStateDirty = true; }
	private:

		AnimationState m_AnimState{};
		bool m_AnimStateDirty{ true };

		SDL_Rect m_SrcRect{};
		float m_LastSpriteUpdate{ };
		float m_MaxSpriteUpdate{ 0.1f };

		float m_DeadLastSpriteUpdate{ };
		float m_DeadMaxSpriteUpdate{ 1.f/4.f };

		int m_Score{};

		GameObject* m_pPlayer{};
	};
}