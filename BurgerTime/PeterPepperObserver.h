#pragma once
#include "AIComponent.h"
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "MovementComponent.h"
#include "Observer.h"
#include "SceneManager.h"

class LadderObserver : public dae::Observer
{
public:
	virtual ~LadderObserver() = default;
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

	explicit LadderObserver(dae::GameObject* pPlayer)
	{
		m_pPlayer = pPlayer;
	}
	LadderObserver() = default;
	LadderObserver(const LadderObserver& other) = delete;
	LadderObserver(LadderObserver&& other) noexcept = delete;
	LadderObserver& operator=(const LadderObserver& other) = delete;
	LadderObserver& operator=(LadderObserver&& other) noexcept = delete;

private:
	dae::GameObject* m_pPlayer{};
};

class PetterPepperObserver : public dae::Observer
{
public:
	virtual ~PetterPepperObserver() = default;
	void OnNotify(dae::GameObject * /*pGo*/, dae::Event event) override
	{
		switch (event)
		{
		case dae::Event::Restart:
		{
			dae::SceneManager::GetInstance().RestartScene();
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

