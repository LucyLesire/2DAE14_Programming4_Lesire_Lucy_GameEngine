#pragma once
#include "AIComponent.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "MovementComponent.h"
#include "Observer.h"
#include "SceneManager.h"

class CollisionObserver : public dae::Observer
{
public:
	~CollisionObserver() override = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event) override
	{
		switch (event)
		{
		case dae::Event::Collide:
		{
			if (auto pEnemyAIComp = pGo->GetComponent<dae::AIComponent>())
			{
				if (!pEnemyAIComp->GetStunned())
					m_pPlayer->GetComponent<dae::PetterPepperComponent>()->Die();
			}
		}
		break;
		}
	}

	explicit CollisionObserver(dae::GameObject* pPlayer)
	{
		m_pPlayer = pPlayer;
	}
	CollisionObserver() = default;
	CollisionObserver(const CollisionObserver& other) = delete;
	CollisionObserver(CollisionObserver&& other) noexcept = delete;
	CollisionObserver& operator=(const CollisionObserver& other) = delete;
	CollisionObserver& operator=(CollisionObserver&& other) noexcept = delete;

private:
	dae::GameObject* m_pPlayer{};
};

class PetterPepperObserver : public dae::Observer
{
public:
	~PetterPepperObserver() override = default;
	void OnNotify(dae::GameObject * /*pGo*/, dae::Event event) override
	{
		switch (event)
		{
		case dae::Event::Restart:
		{
			dae::SceneManager::GetInstance().RestartScene();
		}
		break;
		case dae::Event::NoLives:
		{
			dae::SceneManager::GetInstance().SetActiveScene(dae::SceneManager::GetInstance().GetSceneAtIndex(0));
		}
		break;
		}
	}

	PetterPepperObserver() = default;
	PetterPepperObserver(const PetterPepperObserver& other) = delete;
	PetterPepperObserver(PetterPepperObserver&& other) noexcept = delete;
	PetterPepperObserver& operator=(const PetterPepperObserver& other) = delete;
	PetterPepperObserver& operator=(PetterPepperObserver&& other) noexcept = delete;
};

