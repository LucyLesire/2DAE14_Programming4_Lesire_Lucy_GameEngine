#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "Subject.h"

dae::BaseComponent::BaseComponent(GameObject* pOwner)
	: m_pOwner(pOwner)
{
	m_pSubject = std::make_unique<Subject>();
}
