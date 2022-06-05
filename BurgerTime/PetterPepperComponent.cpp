#include "PetterPepperComponent.h"

#include <SDL_rect.h>

#include "Command.h"
#include "ImageComponent.h"
#include "MovementComponent.h"
#include "Observer.h"
#include "Subject.h"

void dae::PetterPepperComponent::Update(float dt)
{
	if(m_Dead)
	{
		m_DeadTime -= dt;
		if(m_DeadTime <= 0.f)
		{
			GetSubject()->Notify(GetOwner(), Event::Restart);
		}
	}


	if(m_PepperedTile)
	{
		if(m_PepperedTile->m_Peppered)
		{
			m_PepperTime -= dt;
			if(m_PepperTime <= 0.f)
			{
				m_PepperTime = m_MaxPepperTime;
				m_PepperedTile->m_Peppered = false;

				size_t childAmount = GetOwner()->GetChildCount();
				for (size_t i{}; i < childAmount; ++i)
				{
					auto child = GetOwner()->GetChildAt(i);
					if (child->GetTag() == "Pepper")
					{
						child->GetComponent<ImageComponent>()->SetActive(false);
					}
				}
			}
		}
	}

	if(auto moveComp = GetOwner()->GetComponent<MovementComponent>())
	{
		if(m_AnimState != AnimationState::Dead)
		{
			if (m_AnimState != AnimationState::WalkingLeft)
			{
				if (moveComp->GetMoveDir().GetPosition().x < -0.1f)
					SetAnimState(AnimationState::WalkingLeft);
			}
			if (m_AnimState != AnimationState::WalkingRight)
			{
				if (moveComp->GetMoveDir().GetPosition().x > 0.1f)
					SetAnimState(AnimationState::WalkingRight);
			}
			if (m_AnimState != AnimationState::Idle)
			{
				if (moveComp->GetMoveDir().GetPosition().x >= -0.1f && moveComp->GetMoveDir().GetPosition().x <= 0.1f)
					if (moveComp->GetMoveDir().GetPosition().y >= -0.1f && moveComp->GetMoveDir().GetPosition().y <= 0.1f)
						SetAnimState(AnimationState::Idle);
			}
			if (m_AnimState != AnimationState::WalkingLadder)
			{
				if (moveComp->GetMoveDir().GetPosition().y >= 0.1f || moveComp->GetMoveDir().GetPosition().y <= -0.1f)
					SetAnimState(AnimationState::WalkingLadder);
			}

		}

	}

	UpdateAnimations(dt);

}

void dae::PetterPepperComponent::FixedUpdate(float)
{
}

dae::PetterPepperComponent::PetterPepperComponent(GameObject* pOwner)
	:BaseComponent(pOwner)
{
	SetWorldTransform(pOwner->GetWorldPosition());
	m_LastSpriteUpdate = m_MaxSpriteUpdate;
	m_PepperTime = m_MaxPepperTime;
}

void dae::PetterPepperComponent::Die()
{
	if(!m_Dead)
	{
		m_Lives--;
		GetSubject()->Notify(GetOwner(), Event::Died);

		m_AnimState = AnimationState::Dead;
		m_AnimStateDirty = true;
		GetOwner()->GetComponent<MovementComponent>()->Died();
		m_Dead = true;
	}
}

void dae::PetterPepperComponent::AddPoints()
{
	const int addedPoints = 50;
	m_Points += addedPoints;
	GetSubject()->Notify(GetOwner(), Event::GotPoints);
}

void dae::PetterPepperComponent::Pepper()
{
	auto& tileManager = TileManager::GetInstance();
	auto playerDir = GetOwner()->GetComponent<MovementComponent>()->GetMoveDir().GetPosition().x;
	if (playerDir <= 0.01f && playerDir >= -0.01f)
	{
		playerDir = -1.f;
	}
	auto offset = tileManager.GetTileWidth() * playerDir;

	auto nextTile = tileManager.GetTileAtPosition({ GetOwner()->GetWorldPosition().GetPosition().x + offset, GetOwner()->GetWorldPosition().GetPosition().y });
	nextTile->m_Peppered = true;
	m_PepperedTile = nextTile;

	size_t childAmount = GetOwner()->GetChildCount();
	for(size_t i{}; i < childAmount; ++i)
	{
		auto child = GetOwner()->GetChildAt(i);
		if(child->GetTag() == "Pepper")
		{
			child->GetComponent<ImageComponent>()->SetActive(true);
			child->SetPosition(playerDir * 50.f, 0.f);
		}
	}
}

void dae::PetterPepperComponent::UpdateAnimations(float dt)
{
	auto imgComp = GetOwner()->GetComponent<ImageComponent>();
	auto imageSize = imgComp->GetSheetSize();
	int spriteSizeX = static_cast<int>(imageSize.GetPosition().x / 9.f);
	auto spriteSizeY = static_cast<int>(imageSize.GetPosition().y / 2.f);

	switch (m_AnimState)
	{
	case AnimationState::Idle:
	{
		if (m_AnimStateDirty)
		{
			m_SrcRect.x = 0;
			m_SrcRect.y = 0;
			m_SrcRect.w = spriteSizeX;
			m_SrcRect.h = spriteSizeY;
			m_AnimStateDirty = false;
		}
		else
		{
			m_LastSpriteUpdate -= dt;
			if (m_LastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 2 * spriteSizeX)
				{
					m_SrcRect.x = 0;
				}
				m_LastSpriteUpdate = m_MaxSpriteUpdate;
			}
		}
		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(false);
		break;
	}
	case AnimationState::WalkingLeft:
	{
		if (m_AnimStateDirty)
		{
			m_SrcRect.x = 3 * spriteSizeX;
			m_SrcRect.y = 0;
			m_SrcRect.w = spriteSizeX;
			m_SrcRect.h = spriteSizeY;
			m_AnimStateDirty = false;
		}
		else
		{
			m_LastSpriteUpdate -= dt;
			if (m_LastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 5 * spriteSizeX)
				{
					m_SrcRect.x = 3 * spriteSizeX;
				}
				m_LastSpriteUpdate = m_MaxSpriteUpdate;
			}
		}

		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(false);
		break;
	}
	case AnimationState::WalkingRight:
	{
		if (m_AnimStateDirty)
		{
			m_SrcRect.x = 3 * spriteSizeX;
			m_SrcRect.y = 0;
			m_SrcRect.w = spriteSizeX;
			m_SrcRect.h = spriteSizeY;
			m_AnimStateDirty = false;
		}
		else
		{
			m_LastSpriteUpdate -= dt;
			if (m_LastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 5 * spriteSizeX)
				{
					m_SrcRect.x = 3 * spriteSizeX;
				}
				m_LastSpriteUpdate = m_MaxSpriteUpdate;
			}

		}

		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(true);
		break;
	}
	case AnimationState::WalkingLadder:
	{
		if (m_AnimStateDirty)
		{
			m_SrcRect.x = 6 * spriteSizeX;
			m_SrcRect.y = 0;
			m_SrcRect.w = spriteSizeX;
			m_SrcRect.h = spriteSizeY;
			m_AnimStateDirty = false;
		}
		else
		{
			m_LastSpriteUpdate -= dt;
			if (m_LastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 8 * spriteSizeX)
				{
					m_SrcRect.x = 6 * spriteSizeX;
				}
				m_LastSpriteUpdate = m_MaxSpriteUpdate;
			}

		}
		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(false);
		break;
	}
	case AnimationState::Dead:
	{
		if (m_AnimStateDirty)
		{
			m_SrcRect.x = 3 * spriteSizeX;
			m_SrcRect.y = spriteSizeY;
			m_SrcRect.w = spriteSizeX;
			m_SrcRect.h = spriteSizeY;
			m_AnimStateDirty = false;
		}
		else
		{
			m_LastSpriteUpdate -= dt;
			if (m_LastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 8 * spriteSizeX)
				{
					m_SrcRect.x = 3 * spriteSizeX;
				}
				m_LastSpriteUpdate = m_MaxSpriteUpdate;
			}

		}
		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(false);
		break;
	}
	}

}
