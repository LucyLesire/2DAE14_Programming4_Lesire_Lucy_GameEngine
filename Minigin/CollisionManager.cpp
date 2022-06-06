#include "MiniginPCH.h"
#include "CollisionManager.h"

#include "CollisionComponent.h"
#include "Observer.h"


void dae::CollisionManager::Update(float)
{
	for (auto pCollider : m_pColliders)
	{
		if (pCollider->IsActive())
		{
			for (auto pOtherCollider : m_pColliders)
			{
				//Ignore self
				if (pCollider == pOtherCollider)
					continue;

				//Notify on collision with what object
				bool colliding = pCollider->CollideCheck(pOtherCollider);
				if (colliding)
				{
					dae::GameObject* pCollidingObject = pOtherCollider->GetOwner();
					if(pCollidingObject)
						pCollider->GetSubject()->Notify(pCollidingObject, dae::Event::Collide);
				}
			}
		}
	}
}

void dae::CollisionManager::AddCollider(dae::CollisionComponent* pCollider)
{
	m_pColliders.push_back(pCollider);
}

