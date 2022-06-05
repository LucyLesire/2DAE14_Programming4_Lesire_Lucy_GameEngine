#pragma once
#include "BaseComponent.h"
#include <memory>
#include <SDL_rect.h>
#include <vector>

struct Tile;

namespace dae
{
	enum class AnimationState
	{
		WalkingLeft,
		WalkingRight,
		WalkingLadder,
		Idle,
		Dead
	};

	class Subject;
	class PetterPepperComponent final : public BaseComponent
	{
	public:
		void Update(float dT) override;
		void FixedUpdate(float fDT) override;
		void Initialize() override {};
		void LateUpdate(float) override {};

		PetterPepperComponent(GameObject* pOwner);
		virtual ~PetterPepperComponent() = default;
		PetterPepperComponent(const PetterPepperComponent& other) = delete;
		PetterPepperComponent(PetterPepperComponent&& other) = delete;
		PetterPepperComponent& operator=(const PetterPepperComponent& other) = delete;
		PetterPepperComponent& operator=(PetterPepperComponent&& other) = delete;

		void Die();
		void AddPoints();
		void Pepper();
		void PlaySound();
		int GetLives() const { return m_Lives; };
		int GetPoints() const { return m_Points; };

		void SetAnimState(AnimationState newState) { m_AnimState = newState; m_AnimStateDirty = true; }
	private:
		int m_Lives{ 3 };
		int m_Points{ 0 };

		AnimationState m_AnimState{};
		bool m_AnimStateDirty{};

		SDL_Rect m_SrcRect{};

		float m_LastSpriteUpdate{ };
		float m_MaxSpriteUpdate{ 0.1f };

		Tile* m_PepperedTile{};
		float m_PepperTime{};
		float m_MaxPepperTime{ 0.5f };

		bool m_Dead{};
		float m_DeadTime{2.f};

		void UpdateAnimations(float dt);
	};
}


