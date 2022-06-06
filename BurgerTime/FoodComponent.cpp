#include "FoodComponent.h"

#include "GameObject.h"
#include "Observer.h"
#include "PetterPepperComponent.h"
#include "TileManager.h"

void FoodComponent::Update(float)
{
	for (int i{}; i < m_CurrentTiles.size(); ++i)
	{
		if(m_CurrentTiles[i]->m_IsTriggered)
		{
			m_Walked[i] = true;
			m_CurrentTiles[i]->m_Pushed = false;
		}
	}
	if(m_CurrentTiles[0]->m_Pushed)
	{
		for (int i{}; i < m_CurrentTiles.size(); ++i)
		{
			m_Walked[i] = true;
			m_CurrentTiles[i]->m_Pushed = false;
			m_CurrentTiles[i]->m_IsTriggered = false;
		}
	}
}

void FoodComponent::FixedUpdate(float fDT)
{
	if(m_Walked[0] == true && m_Walked[1] == true && m_Walked[2] == true && m_Walked[3] == true)
	{
		Fall(fDT);
	}
}

void FoodComponent::Initialize()
{
	m_Type = m_CurrentTiles[0]->m_ExtraType;
}

void FoodComponent::Fall(float fDt)
{
	//Initializing tiles
	auto& tileManager = TileManager::GetInstance();
	Tile* underTile = tileManager.GetTileAtIndex(m_CurrentTiles[0]->m_Index + 1);

	//Initializing positions
	auto prevPos = GetOwner()->GetWorldPosition().GetPosition();
	auto newPosY = prevPos.y + m_FallSpeed * fDt;
	for (int i{}; i < m_CurrentTiles.size(); ++i)
	{
		m_CurrentTiles[i]->m_Falling = true;
	}

	//Check if falling on other ingredient
	if(underTile->m_ExtraType != ExtraType::Empty)
	{
		m_MaxY = underTile->m_Boundingbox.y;
		underTile->m_Pushed = true;
		for (int i{}; i < m_CurrentTiles.size(); ++i)
		{
			m_CurrentTiles[i]->m_Falling = false;
		}
	}

	//Check if falling in tray
	if (underTile->m_Type == TileType::Tray)
	{
		for (int i{}; i < m_CurrentTiles.size(); ++i)
		{
			auto newTile = tileManager.GetTileAtIndex(m_CurrentTiles[i]->m_Index + 1);
			m_CurrentTiles[i]->m_Type = newTile->m_Type;
			m_CurrentTiles[i]->m_Pushed = false;
			m_CurrentTiles[i]->m_Falling = false;
			m_Walked[i] = false;
		}
		if(m_Type == ExtraType::TopBun)
		{
			m_pPlayer->GetComponent<dae::PetterPepperComponent>()->GetSubject()->Notify(m_pPlayer, dae::Event::BurgerCompleted);
		}
		return;
	}

	//Stop falling
	if (newPosY >= m_MaxY - 1.f)
	{
		GetOwner()->SetPosition(prevPos.x, m_MaxY);
		m_MaxY = 5000.f;
		for (int i{}; i < m_CurrentTiles.size(); ++i)
		{
			auto offset = i * tileManager.GetTileWidth();
			auto newTile = tileManager.GetTileAtPosition({ GetOwner()->GetWorldPosition().GetPosition().x + offset, GetOwner()->GetWorldPosition().GetPosition().y });

			m_CurrentTiles[i] = newTile;
			m_CurrentTiles[i]->m_Falling = false;
			m_CurrentTiles[i]->m_Pushed = false;
			m_Walked[i] = false;
		}
		m_pPlayer->GetComponent<dae::PetterPepperComponent>()->GetSubject()->Notify(m_pPlayer, dae::Event::BurgerDropped);
	}
	else
	{
		//Fall
		GetOwner()->SetPosition(prevPos.x, newPosY);

		//Update tiles
		for (int i{}; i < m_CurrentTiles.size(); ++i)
		{
			auto offset = i * tileManager.GetTileWidth();
			auto newTile = tileManager.GetTileAtPosition({ GetOwner()->GetWorldPosition().GetPosition().x + offset, GetOwner()->GetWorldPosition().GetPosition().y });

			if (newTile != m_CurrentTiles[i])
			{
				m_CurrentTiles[i]->m_Falling = false;
				m_CurrentTiles[i] = newTile;
				m_CurrentTiles[i]->m_Pushed = false;
			}
		}

	}
}

FoodComponent::FoodComponent(dae::GameObject* pOwner, dae::GameObject* pPlayer,float fallSpeed)
	:BaseComponent(pOwner)
	,m_FallSpeed(fallSpeed)
	,m_MaxY(50000.f)
	,m_pPlayer(pPlayer)
{
	
}


