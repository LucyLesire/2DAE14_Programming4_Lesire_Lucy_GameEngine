#pragma once
#include <memory>
#include <string>
#include <vector>

#include "GameInstance.h"
#include "Observer.h"
#include "PetterPepperComponent.h"

class HealthDisplay : public dae::Observer
{
public:
	virtual ~HealthDisplay() = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event)
	{
		switch (event)
		{
		case dae::Event::Died:
			auto pp = pGo->GetComponent<dae::PetterPepperComponent>();
			const std::string liveTemplate = "Lives: ";
			if (pp)
			{
				m_pTextComp->SetText(liveTemplate + std::to_string(pp->GetLives()));
			}

		}
	}


	HealthDisplay(const std::shared_ptr<dae::TextComponent>& pTextComponent)
		:m_pTextComp(pTextComponent)
	{
	};

private:
	std::shared_ptr<dae::TextComponent> m_pTextComp;
};

class PointDisplay : public dae::Observer
{
public:
	virtual ~PointDisplay() = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event)
	{
		auto pp = pGo->GetComponent<dae::PetterPepperComponent>();
		switch (event)
		{
		case dae::Event::BurgerDropped:
			pp->AddPoints(50);
			if (pp)
			{
				m_pTextComponent->SetText(m_ScoreTemplate + std::to_string(pp->GetPoints()));
			}
			break;
		case dae::Event::BurgerCompleted:
			pp->AddPoints(500);
			if (pp)
			{
				m_pTextComponent->SetText(m_ScoreTemplate + std::to_string(pp->GetPoints()));
			}
			GameInstance::GetInstance().AddBurgersDropped();
			break;
		case dae::Event::EnemyKilled:
			if (pp)
			{
				m_pTextComponent->SetText(m_ScoreTemplate + std::to_string(pp->GetPoints()));
			}
			break;
		}
	}


	PointDisplay(const std::shared_ptr<dae::TextComponent>& pTextComponent)
		:m_pTextComponent(pTextComponent)
	{
	};
private:
	std::shared_ptr<dae::TextComponent> m_pTextComponent;
	const std::string m_ScoreTemplate = "Score: ";
};

