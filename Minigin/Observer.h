#pragma once
#include "GameObject.h"
#include "TextComponent.h"
#include "PetterPepperComponent.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"

namespace dae
{
	class GameObject;

	enum class Event
	{
		Died,
		GotPoints
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(GameObject* pGo, Event event) = 0;
	protected:
		Observer() = default;
	};

	class HealthDisplay : public Observer
	{
	public:
		virtual ~HealthDisplay() = default;
		void OnNotify(GameObject* pGo, Event event)
		{
			switch(event)
			{
			case Event::Died:
				auto pp = pGo->GetComponent<PetterPepperComponent>();
				const std::string liveTemplate = "Lives: ";
				if(pp)
				{
					m_pTextComp->SetText(liveTemplate + std::to_string(pp->GetLives()));
				}

			}
		}


		HealthDisplay(const std::shared_ptr<TextComponent>& pTextComponent)
			:m_pTextComp(pTextComponent)
		{
		};

	private:
		std::shared_ptr<TextComponent> m_pTextComp;
	};

	class PointDisplay: public Observer
	{
	public:
		virtual ~PointDisplay() = default;
		void OnNotify(GameObject* pGo, Event event)
		{
			switch (event)
			{
			case Event::GotPoints:
				auto pp = pGo->GetComponent<PetterPepperComponent>();
				const std::string liveTemplate = "Points: ";
				if (pp)
				{
					m_pTextComponent->SetText(liveTemplate + std::to_string(pp->GetPoints()));
				}

			}
		}


		PointDisplay(const std::shared_ptr<TextComponent>& pTextComponent)
			:m_pTextComponent(pTextComponent)
		{
		};
	private:
		std::shared_ptr<TextComponent> m_pTextComponent;
	};
};



