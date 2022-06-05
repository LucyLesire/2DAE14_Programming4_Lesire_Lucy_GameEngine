#include "MiniginPCH.h"
#include "CollisionComponent.h"

#include "GameObject.h"

dae::CollisionComponent::CollisionComponent(GameObject* pOwner, bool active, float width, float height, bool centered)
	:BaseComponent(pOwner)
	,m_Active(active)
	,m_Width(width)
	,m_Height(height)
	,m_Centered(centered)
{

}

void dae::CollisionComponent::Initialize()
{
	//Set location of collision box, taking into account the parent object's transform
	const auto& parentPos = GetOwner()->GetWorldPosition().GetPosition();
	const auto& compPos = GetLocalTransform().GetPosition();
	if(m_Centered)
	{
		m_ColBox2D.m_BottomLeft.SetPosition((parentPos.x + compPos.x) - (m_Width / 2.f), (parentPos.y + compPos.y) + (m_Height / 2.f));
	}
	else
	{
		m_ColBox2D.m_BottomLeft.SetPosition((parentPos.x + compPos.x), (parentPos.y + compPos.y));
	}
	m_ColBox2D.m_Size.SetPosition(m_Width, m_Height);
}


void dae::CollisionComponent::Update(float)
{
	const auto& parentPos = GetOwner()->GetWorldPosition().GetPosition();
	const auto& compPos = GetLocalTransform().GetPosition();
	if (m_Centered)
	{
		m_ColBox2D.m_BottomLeft.SetPosition((parentPos.x + compPos.x) - (m_Width / 2.f), (parentPos.y + compPos.y) + (m_Height / 2.f));
	}
	else
	{
		m_ColBox2D.m_BottomLeft.SetPosition((parentPos.x + compPos.x), (parentPos.y + compPos.y));
	}
}

bool dae::CollisionComponent::CollideCheck(CollisionComponent* pCollider) const
{
	if (!pCollider->IsActive() || !IsActive())
		return false;

	const auto& bottomLeft = m_ColBox2D.m_BottomLeft.GetPosition();
	const auto& size = m_ColBox2D.m_Size.GetPosition();

	const auto& otherColBox = pCollider->GetCollisionBox2D();
	const auto& otherBottomLeft = otherColBox.m_BottomLeft.GetPosition();
	const auto& otherSize = otherColBox.m_Size.GetPosition();

	if(bottomLeft.x <= otherBottomLeft.x + otherSize.x && bottomLeft.x + size.x >= otherBottomLeft.x)
	{
		if(bottomLeft.y <= otherBottomLeft.y + otherSize.y && bottomLeft.y + size.y >= otherBottomLeft.y)
		{
			return true;
		}
	}

	return false;
}
