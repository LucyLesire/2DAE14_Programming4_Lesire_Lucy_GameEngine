#include "MiniginPCH.h"
#include "Subject.h"
#include "Observer.h"
#include "GameObject.h"

dae::Subject::Subject()
	:m_AmountObservers(0)
{

}

void dae::Subject::AddObserver(std::shared_ptr<Observer> pObserver)
{
	m_AmountObservers++;
	m_pObservers.push_back(pObserver);
}

void dae::Subject::RemoveObserver(std::shared_ptr<Observer> pObserver)
{
	auto removeIt = std::remove(m_pObservers.begin(), m_pObservers.end(), pObserver);
	m_pObservers.erase(removeIt);
}

void dae::Subject::Notify(GameObject* pGo, Event event)
{
	for(const auto& o: m_pObservers)
	{
		o->OnNotify(pGo, event);
	}
}
