#include "AIComponent.h"

#include "GameObject.h"
#include "MovementComponent.h"
#include "Observer.h"
#include "PetterPepperComponent.h"
#include "TileManager.h"

dae::AIComponent::AIComponent(GameObject* pOwner, GameObject* pPlayer, float speed, bool lefty)
	:BaseComponent(pOwner)
	,m_pPlayer(pPlayer)
	,m_Speed(speed)
	,m_Lefty(lefty)
{
	m_SquishedTime = m_MaxSquishedTime;
	m_StunnedTime = m_MaxStunnedTime;
}


void dae::AIComponent::Update(float dt)
{
	if (m_Stunned)
		ResetStunned(dt);

	if (!m_Squished)
		CalculatePath(m_pPlayer->GetWorldPosition());
	else
		Squished(dt);
}

void dae::AIComponent::ResetStunned(float dt)
{
	m_StunnedTime -= dt;
	if(m_StunnedTime <= 0.f)
	{
		m_Stunned = false;
		m_StunnedTime = m_MaxStunnedTime;
	}
}

void dae::AIComponent::CalculatePath(const Transform& toPos)
{
	if (m_Stunned)
		return;

	auto& tileManager = TileManager::GetInstance();
	auto currentTile = tileManager.GetTileAtPosition(GetOwner()->GetWorldPosition().GetPosition());

	if (currentTile->m_Falling)
	{
		m_Squished = true;
		return;
	}

	auto moveComp = GetOwner()->GetComponent<MovementComponent>();

	if (currentTile->m_Peppered)
	{
		moveComp->MoveRight(false);
		moveComp->MoveUpLadder(false);
		m_Stunned = true;
		return;
	}

	auto fromTilePos = currentTile->m_Boundingbox;
	auto toTilePos = tileManager.GetTileAtPosition(toPos.GetPosition())->m_Boundingbox;
	auto offSet = tileManager.GetTileWidth();

	if(m_Stuck)
	{
		if(m_GetOutOfStuck.GetPosition().x == currentTile->m_Boundingbox.x && m_GetOutOfStuck.GetPosition().y == currentTile->m_Boundingbox.y)
		{
			m_Stuck = false;
		}
		else
		{
			toTilePos.x = m_GetOutOfStuck.GetPosition().x;
			toTilePos.y = m_GetOutOfStuck.GetPosition().y;
		}
	}

	if(currentTile->m_Type != TileType::Ladder)
	{
		if (fromTilePos.x < toTilePos.x)
		{
			auto rightTile = tileManager.GetTileAtPosition({ fromTilePos.z + offSet, fromTilePos.y });
			if (rightTile->m_Type != TileType::Empty)
			{
				moveComp->MoveRight(true);
				moveComp->MoveDownLadder(false);
				moveComp->MoveUpLadder(false);
			}
			else
			{
				if (fromTilePos.y > toTilePos.y)
				{
					auto upTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w - offSet });
					if (upTile->m_Type != TileType::Empty)
					{
						moveComp->MoveRight(false);
						moveComp->MoveUpLadder(true);
					}
				}
				else
				{
					auto downTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w + offSet });
					if (downTile->m_Type != TileType::Empty)
					{
						moveComp->MoveRight(false);
						moveComp->MoveDownLadder(true);
					}
				}
			}
		}
		else if (fromTilePos.x > toTilePos.x)
		{
			auto leftTile = tileManager.GetTileAtPosition({ fromTilePos.z - offSet, fromTilePos.y });
			if (leftTile->m_Type != TileType::Empty)
			{
				moveComp->MoveLeft(true);
				moveComp->MoveDownLadder(false);
				moveComp->MoveUpLadder(false);
			}
			else
			{
				if (fromTilePos.y > toTilePos.y)
				{
					auto upTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w - offSet });
					if (upTile->m_Type != TileType::Empty)
					{
						moveComp->MoveLeft(false);
						moveComp->MoveUpLadder(true);
					}
				}
				else
				{
					auto downTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w + offSet });
					if (downTile->m_Type != TileType::Empty)
					{
						moveComp->MoveLeft(false);
						moveComp->MoveDownLadder(true);
					}
				}
			}
		}
		else
		{
			if (fromTilePos.y > toTilePos.y)
			{
				auto upTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.y - offSet + 1.f });
				if (upTile->m_Type == TileType::Ladder || (upTile->m_Type == TileType::Floor && currentTile->m_Type != TileType::Floor))
				{
					moveComp->MoveLeft(false);
					moveComp->MoveUpLadder(true);
				}
				else
				{
					m_Stuck = true;
					auto rightTile = tileManager.GetTileAtPosition({ fromTilePos.x + offSet, fromTilePos.w });
					for (int i{}; rightTile->m_Type != TileType::Empty; ++i)
					{
						rightTile = tileManager.GetTileAtPosition({ fromTilePos.x + (i * offSet), fromTilePos.w });
					}
					m_GetOutOfStuck.SetPosition(rightTile->m_Boundingbox.z, toTilePos.y, 0.f);

				}
			}
			else
			{
				auto downTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w + offSet });
				if (downTile->m_Type != TileType::Empty)
				{
					moveComp->MoveLeft(false);
					moveComp->MoveDownLadder(true);
				}
				else
				{
					m_Stuck = true;
					auto rightTile = tileManager.GetTileAtPosition({ fromTilePos.x + offSet, fromTilePos.w });
					for (int i{}; rightTile->m_Type != TileType::Empty; ++i)
					{
						rightTile = tileManager.GetTileAtPosition({ fromTilePos.x + (i * offSet), fromTilePos.w });
					}
					m_GetOutOfStuck.SetPosition(rightTile->m_Boundingbox.z, toTilePos.y, 0.f);
				}
			}
		}
	}
	else
	{
		if (fromTilePos.y > toTilePos.y)
		{
			auto upTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w - offSet });
			if (upTile->m_Type != TileType::Empty)
			{
				moveComp->MoveLeft(false);
				moveComp->MoveUpLadder(true);
			}
		}
		else
		{
			auto downTile = tileManager.GetTileAtPosition({ fromTilePos.x, fromTilePos.w + offSet });
			if (downTile->m_Type != TileType::Empty)
			{
				moveComp->MoveLeft(false);
				moveComp->MoveDownLadder(true);
			}
		}
	}
}

void dae::AIComponent::Squished(float dt)
{
	auto moveComp = GetOwner()->GetComponent<MovementComponent>();

	moveComp->MoveLeft(false);
	moveComp->MoveDownLadder(false);

	m_SquishedTime -= dt;
	if(m_SquishedTime <= 0)
	{
		GetOwner()->Destroy();
		m_pPlayer->GetComponent<PetterPepperComponent>()->GetSubject()->Notify(m_pPlayer, Event::GotPoints);
	}
}

