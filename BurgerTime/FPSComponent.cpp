#include "FPSComponent.h"
#include "BaseComponent.h"
#include <string>
#include "TextComponent.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Transform.h"

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
		if (GetOwner()->GetComponent<TextComponent>())
		{
			GetOwner()->GetComponent<TextComponent>()->SetText(std::to_string(int(std::roundf(1 / dT))));
			m_CanChange = false;
		}
	}
}

dae::FPSComponent::FPSComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
	
}
