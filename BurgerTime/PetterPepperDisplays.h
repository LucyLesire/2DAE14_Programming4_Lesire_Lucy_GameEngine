#pragma once
#include <memory>
#include <string>
#include <vector>

#include "GameInstance.h"
#include "ImageComponent.h"
#include "Observer.h"
#include "PetterPepperComponent.h"

class HealthDisplay : public dae::Observer
{
public:
	~HealthDisplay() override = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event) override
	{
		switch (event)
		{
		case dae::Event::Died:
			auto pp = pGo->GetComponent<dae::PetterPepperComponent>();
			if (pp)
			{
				auto lives = GameInstance::GetInstance().GetLives();
				if(lives > 0)
				{
					SDL_Rect srcRect{ 0, 0, static_cast<int>(static_cast<unsigned int>(m_pImageComponent->GetSheetSize().GetPosition().x) / 3.f * lives),static_cast<int>(m_pImageComponent->GetSheetSize().GetPosition().y) };
					m_pImageComponent->SetSrcRect(srcRect);
					m_pImageComponent->SetSize({ m_pImageComponent->GetSize().GetPosition().x / 3.f * lives ,m_pImageComponent->GetSize().GetPosition().y });
				}
		}
		}
	}


	HealthDisplay(const std::shared_ptr<dae::ImageComponent>& pTextComponent)
		:m_pImageComponent(pTextComponent)
	{
		auto lives = GameInstance::GetInstance().GetLives();
		if (lives > 0)
		{
			SDL_Rect srcRect{ 0, 0, static_cast<int>(static_cast<unsigned int>(m_pImageComponent->GetSheetSize().GetPosition().x) / 3.f * lives),static_cast<int>(m_pImageComponent->GetSheetSize().GetPosition().y) };
			m_pImageComponent->SetSrcRect(srcRect);
			m_pImageComponent->SetSize({ m_pImageComponent->GetSize().GetPosition().x / 3.f * lives ,m_pImageComponent->GetSize().GetPosition().y });
		}
	};

private:
	std::shared_ptr<dae::ImageComponent> m_pImageComponent;
};

class PointDisplay : public dae::Observer
{
public:
	~PointDisplay() override = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event) override
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
		m_pTextComponent->SetText(m_ScoreTemplate + std::to_string(GameInstance::GetInstance().GetScore()));
	};
private:
	std::shared_ptr<dae::TextComponent> m_pTextComponent;
	const std::string m_ScoreTemplate = "Score: ";
};

