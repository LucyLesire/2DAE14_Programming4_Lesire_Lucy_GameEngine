#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

void dae::FPSComponent::Update(float dT)
{
	if (m_CanChange == false)
	{
		m_WaitBetweenUpdates += dT;
		if (m_WaitBetweenUpdates > m_MaxWait)
		{
			m_WaitBetweenUpdates = 0.f;
			m_CanChange = true;
		}
	}
	else
	{
		if (GetOwner().lock()->GetComponent<TextComponent>())
		{
			GetOwner().lock()->GetComponent<TextComponent>()->SetText(std::to_string(int(std::roundf(1 / dT))));
			m_CanChange = false;
		}
	}
}

dae::FPSComponent::FPSComponent(std::weak_ptr<GameObject> owner)
	:BaseComponent(owner)
{
	
}
