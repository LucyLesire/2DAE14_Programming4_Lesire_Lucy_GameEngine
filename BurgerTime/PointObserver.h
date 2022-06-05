#pragma once
#include <string>

#include "Observer.h"
#include "PetterPepperComponent.h"

class PointObserver : public dae::Observer
{
public:
	virtual ~PointObserver() = default;
	void OnNotify(dae::GameObject* pGo, dae::Event event)
	{
		switch (event)
		{
		case dae::Event::GotPoints:
			auto pp = pGo->GetComponent<dae::PetterPepperComponent>();
			const std::string liveTemplate = "Points: ";
			if (pp)
			{
				m_pTextComponent->SetText(liveTemplate + std::to_string(50.f));
			}
		}
	}


	PointObserver(const std::shared_ptr<dae::TextComponent>& pTextComponent)
		:m_pTextComponent(pTextComponent)
	{
	};
private:
	std::shared_ptr<dae::TextComponent> m_pTextComponent;
};

