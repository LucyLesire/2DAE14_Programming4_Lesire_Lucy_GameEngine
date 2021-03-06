#include "MovementComponent.h"
#include "GameObject.h"
#include "TileManager.h"
#include "Transform.h"

void dae::MovementComponent::Update(float)
{
	//Update tile
	if(m_CurrentTile == nullptr)
	{
		m_CurrentTile = TileManager::GetInstance().GetTileAtPosition({ GetOwner()->GetWorldPosition().GetPosition().x + 25.f , GetOwner()->GetWorldPosition().GetPosition().y });
		m_CurrentTile->m_IsTriggered = true;
	}
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

	//Some movement hacking to make sure you don't go out of bounds
	if (m_CurrentTile->m_Type == TileType::Empty)
	{
		auto& tileManager = TileManager::GetInstance();
		auto rightTile = tileManager.GetTileAtPosition({ m_CurrentTile->m_Boundingbox.w + 2.f, m_CurrentTile->m_Boundingbox.y });
		if (rightTile->m_Type != TileType::Empty)
			MoveRight(true);
		else
		{
			auto leftTile = tileManager.GetTileAtPosition({ m_CurrentTile->m_Boundingbox.x - 2.f, m_CurrentTile->m_Boundingbox.y});
			if (leftTile->m_Type != TileType::Empty)
				MoveLeft(true);
		}

		m_WasStuck = true;
	}

	//Disable the hacking
	if(m_WasStuck)
	{
		if(m_CurrentTile->m_Type != TileType::Empty)
		{
			MoveLeft(false);
			m_WasStuck = false;
		}
	}
}

void dae::MovementComponent::FixedUpdate(float fDT)
{
	if (m_Dead)
		return;

	//Update position according to desired movement direction
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
		//Get left tile
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		pos.x += 25.f;
		auto tileToLeft = tileManager.GetTileAtPosition({ pos.x + (m_CurrentTile->m_Boundingbox.x - m_CurrentTile->m_Boundingbox.z), pos.y });
		//Tile == walkable
		if (tileToLeft->m_Type == TileType::Floor)
		{
			GetOwner()->SetPosition(pos.x - 25.f, m_CurrentTile->m_Boundingbox.y);
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
		//Get right tile
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		auto tileToRight = tileManager.GetTileAtPosition({ pos.x - (m_CurrentTile->m_Boundingbox.x - m_CurrentTile->m_Boundingbox.z), pos.y });
		//Tile == walkable
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
		//Get down tile
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		auto tileToDown = tileManager.GetTileAtPosition({ pos.x + 25.f, pos.y - (pos.y - m_CurrentTile->m_Boundingbox.w) });
		//Tile == climbable
		if (tileToDown->m_Type == TileType::Ladder || tileToDown->m_Type == TileType::Floor)
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
		//Get up tile
		auto& tileManager = TileManager::GetInstance();
		auto pos = GetOwner()->GetWorldPosition().GetPosition();
		auto tileToUp = tileManager.GetTileAtPosition({ pos.x + 25.f, pos.y + (pos.y - m_CurrentTile->m_Boundingbox.w) });
		//Tile == climable
		if (tileToUp->m_Type == TileType::Ladder || tileToUp->m_Type == TileType::Floor)
		{
			m_MoveDir.SetPosition(m_MoveDir.GetPosition().x, -1, m_MoveDir.GetPosition().z);
			return;
		}
	}

	m_MoveDir.SetPosition(m_MoveDir.GetPosition().x, 0, m_MoveDir.GetPosition().z);
}

