#pragma once
#include "CollisionComponent.h"
#include "EnemyComponent.h"
#include "FloorComponent.h"
#include "LadderComponent.h"
#include "MovementComponent.h"
#include "Observer.h"

class LadderObserver : public dae::Observer
{
public:
	virtual ~LadderObserver() = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event) override
	{
		switch (event)
		{
		case dae::Event::CollideLadder:
		{
			if (auto pLadderComp = pGo->GetComponent<LadderComponent>())
			{
				if (!pLadderComp->GetBeingUsed())
				{
					auto moveComp = m_pPlayer->GetComponent<dae::MovementComponent>();
					if (moveComp)
					{
						auto pLadderBotLeft = pGo->GetComponent<dae::CollisionComponent>()->GetCollisionBox2D();
						moveComp->SetOnLadder(true, glm::vec2{ pLadderBotLeft.m_BottomLeft.GetPosition().y ,pLadderBotLeft.m_BottomLeft.GetPosition().y + pLadderBotLeft.m_Size.GetPosition().y });
						pLadderComp->SetBeingUsed(true);
					}
				}
			}
			break;
		}
		case dae::Event::CollideFloor:
		{
			if (auto pFloorComp = pGo->GetComponent<dae::FloorComponent>())
			{
				if (!pFloorComp->GetBeingUsed())
				{
					auto moveComp = m_pPlayer->GetComponent<dae::MovementComponent>();
					if (moveComp)
					{
						auto pFloorBotLeft = pGo->GetComponent<dae::CollisionComponent>()->GetCollisionBox2D();
						moveComp->SetOnFloor(true, glm::vec4{ pFloorBotLeft.m_BottomLeft.GetPosition().x,pFloorBotLeft.m_BottomLeft.GetPosition().x + pFloorBotLeft.m_Size.GetPosition().x, 
							pFloorBotLeft.m_BottomLeft.GetPosition().y, pFloorBotLeft.m_BottomLeft.GetPosition().y + pFloorBotLeft.m_Size.GetPosition().y });
						pFloorComp->SetBeingUsed(true);
						std::cout << "on floor\n";
					}
				}
			}
			break;
		}
		case dae::Event::UnCollideLadder:
		{
			if (auto pLadderComp = pGo->GetComponent<LadderComponent>())
			{
				if (pLadderComp->GetBeingUsed())
				{
					auto moveComp2 = m_pPlayer->GetComponent<dae::MovementComponent>();
					if (moveComp2)
					{
						moveComp2->SetOnLadder(false);
						pLadderComp->SetBeingUsed(false);
					}
				}
			}
			break;
		}
		case dae::Event::UnCollideFloor:
		{
			if (auto pFloorComp = pGo->GetComponent<dae::FloorComponent>())
			{
				if (pFloorComp->GetBeingUsed())
				{
					auto moveComp2 = m_pPlayer->GetComponent<dae::MovementComponent>();
					if (moveComp2)
					{
						moveComp2->SetOnFloor(false);
						pFloorComp->SetBeingUsed(false);
						std::cout << "Left floor\n";
					}
				}
			}
			break;

		}
		case dae::Event::Collide:
			{
				if(pGo->GetComponent<dae::EnemyComponent>())
				{
					m_pPlayer->GetComponent<dae::PetterPepperComponent>()->Die();
				}
			}
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

