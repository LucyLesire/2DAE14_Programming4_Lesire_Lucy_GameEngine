#include "MiniginPCH.h"
#include "PetterPepperComponent.h"

#include "Command.h"
#include "InputManager.h"
#include "Observer.h"
#include "Subject.h"

void dae::PetterPepperComponent::Update(float)
{
}

dae::PetterPepperComponent::PetterPepperComponent(std::weak_ptr<GameObject> pOwner)
	:BaseComponent(pOwner)
{
	SetTransform(pOwner.lock().get()->GetWorldPosition());

	auto healthDisplay = new HealthDisplay();
	healthDisplay->AddActor(this);

	auto pointDisplay = new PointDisplay();
	pointDisplay->AddActor(this);
}

void dae::PetterPepperComponent::Die()
{
	m_Lives--;
	GetSubject()->Notify(shared_from_this(), Event::Died);
}

void dae::PetterPepperComponent::AddPoints()
{
	const int addedPoints = 50;
	m_Points += addedPoints;
	GetSubject()->Notify(shared_from_this(), Event::GotPoints);
}

