#include "MovementComponent.h"
#include "GameObject.h"
#include "TileManager.h"
#include "Transform.h"

void dae::MovementComponent::Update(float)
{
	if(m_CurrentTile == nullptr)
	{
		m_CurrentTile = TileManager::GetInstance().GetTileAtPosition({ GetOwner()->GetWorldPosition().GetPosition().x + 25.f , GetOwner()->GetWorldPosition().GetPosition().y });
		m_CurrentTile->m_IsTriggered = true;
	}


	if (!m_OnLadder)
		m_UsingLadder = false;


	auto newTile = TileManager::GetInstance().GetTileAtPosition({ GetOwner()->GetWorldPosition().GetPosition().x +25.f , GetOwner()->GetWorldPosition().GetPosition().y  });
	if(newTile->m_Index != m_CurrentTile->m_Index)
	{
		if(m_IsPlayer)
		{
			m_CurrentTile->m_IsTriggered = false;
			newTile->m_IsTriggered = true;
		}

		m_CurrentTile = newTile;
	}
}

void dae::MovementComponent::FixedUpdate(float fDT)
{
	if (m_Dead)
		return;

	glm::vec3 prevPos = GetOwner()->GetWorldPosition().GetPosition();
	auto newPos = prevPos + m_MoveDir.GetPosition() * m_Speed * fDT;
	GetOwner()->SetPosition(newPos.x, newPos.y);
}

void dae::MovementComponent::Initialize()
{
	if (GetOwner()->GetTag() == "Peter Pepper")
		m_IsPlayer = true;
}

void dae::MovementComponent::LateUpdate(float)
{

}

dae::MovementComponent::MovementComponent(GameObject* pOwner, float speed)
	:BaseComponent(pOwner)
	,m_Speed(speed)
{
	
}


void dae::MovementComponent::MoveLeft(bool enable)
{
	if (enable)
	{
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		pos.x += 50.f;
		auto tileToLeft = tileManager.GetTileAtPosition({ pos.x + (m_CurrentTile->m_Boundingbox.x - m_CurrentTile->m_Boundingbox.z), pos.y });
		if (tileToLeft->m_Type == TileType::Floor || tileToLeft->m_Boundingbox.x == 0.f)
		{
			GetOwner()->SetPosition(pos.x - 50.f, m_CurrentTile->m_Boundingbox.y);
			m_MoveDir.SetPosition(-1, m_MoveDir.GetPosition().y, m_MoveDir.GetPosition().z);
			return;
		}
	}
	m_MoveDir.SetPosition(0, m_MoveDir.GetPosition().y, m_MoveDir.GetPosition().z);
}

void dae::MovementComponent::MoveRight(bool enable)
{
	if (enable)
	{
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		auto tileToRight = tileManager.GetTileAtPosition({ pos.x - (m_CurrentTile->m_Boundingbox.x - m_CurrentTile->m_Boundingbox.z), pos.y });
		if (tileToRight->m_Type == TileType::Floor || tileToRight->m_Boundingbox.x == 748.f)
		{
			GetOwner()->SetPosition(pos.x, m_CurrentTile->m_Boundingbox.y);
			m_MoveDir.SetPosition(1, m_MoveDir.GetPosition().y, m_MoveDir.GetPosition().z);
			return;
		}
	}
	m_MoveDir.SetPosition(0, m_MoveDir.GetPosition().y, m_MoveDir.GetPosition().z);
}

void dae::MovementComponent::MoveDownLadder(bool enable)
{

	if (enable)
	{
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		auto tileToDown = tileManager.GetTileAtPosition({ pos.x, pos.y - (pos.y - m_CurrentTile->m_Boundingbox.w) });

		if (tileToDown->m_Type == TileType::Ladder || tileToDown->m_Type == TileType::Floor || tileToDown->m_Boundingbox.y == 720.f)
		{
			m_MoveDir.SetPosition(m_MoveDir.GetPosition().x, 1, m_MoveDir.GetPosition().z);
			return;
		}
	}
	m_MoveDir.SetPosition(m_MoveDir.GetPosition().x, 0, m_MoveDir.GetPosition().z);
}

void dae::MovementComponent::MoveUpLadder(bool enable)
{
	if (enable)
	{
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		auto tileToUp = tileManager.GetTileAtPosition({ pos.x, pos.y + (pos.y - m_CurrentTile->m_Boundingbox.w) });
		if (tileToUp->m_Type == TileType::Ladder || tileToUp->m_Type == TileType::Floor)
		{
			m_MoveDir.SetPosition(m_MoveDir.GetPosition().x, -1, m_MoveDir.GetPosition().z);
			return;
		}
	}

	m_MoveDir.SetPosition(m_MoveDir.GetPosition().x, 0, m_MoveDir.GetPosition().z);
}

void dae::MovementComponent::Move(glm::vec2 , bool )
{
	//if(dir.y >= 0.01f)
	//{
	//	MoveUpLadder(enable);
	//}
	//else if(dir.y <= -0.01f)
	//{
	//	MoveDownLadder(enable);
	//}

	//if(dir.x >= 0.01f)
	//{
	//	MoveRight(enable);
	//}
	//else if(dir.x <= -0.01f)
	//{
	//	MoveLeft(enable);
	//}
}

