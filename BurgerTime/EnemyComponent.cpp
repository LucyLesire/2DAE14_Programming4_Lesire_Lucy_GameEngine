#include "EnemyComponent.h"

#include "AIComponent.h"
#include "ImageComponent.h"
#include "GameObject.h"
#include "MovementComponent.h"
#include "Observer.h"

void dae::EnemyComponent::Update(float dT)
{
	if (m_AnimState != AnimationState::Dead && GetOwner()->GetComponent<AIComponent>()->GetSquished())
	{
		m_AnimState = AnimationState::Dead;
		m_AnimStateDirty = true;
		m_pPlayer->GetComponent<dae::PetterPepperComponent>()->AddPoints(m_Score);
		m_pPlayer->GetComponent<dae::PetterPepperComponent>()->GetSubject()->Notify(m_pPlayer, dae::Event::EnemyKilled);
	}
	else if (m_AnimState != AnimationState::WalkingLeft && GetOwner()->GetComponent<MovementComponent>()->GetMoveDir().GetPosition().x < -0.1f)
	{
		m_AnimState = AnimationState::WalkingLeft;
		m_AnimStateDirty = true;
	}
	else if (m_AnimState != AnimationState::WalkingRight && GetOwner()->GetComponent<MovementComponent>()->GetMoveDir().GetPosition().x > 0.1f)
	{
		m_AnimState = AnimationState::WalkingRight;
		m_AnimStateDirty = true;
	}

	auto imgComp = GetOwner()->GetComponent<ImageComponent>();
	auto imageSize = imgComp->GetSheetSize();
	int spriteSizeX = static_cast<int>(imageSize.GetPosition().x / 6.f);
	auto spriteSizeY = static_cast<int>(imageSize.GetPosition().y / 2.f);

	switch (m_AnimState)
	{
	case dae::AnimationState::WalkingLeft:
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
				m_LastSpriteUpdate -= dT;
				if (m_LastSpriteUpdate <= 0.f)
				{
					m_SrcRect.x += spriteSizeX;
					if (m_SrcRect.x > 5 * spriteSizeX)
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
	case dae::AnimationState::WalkingRight:
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
			m_LastSpriteUpdate -= dT;
			if (m_LastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 5 * spriteSizeX)
				{
					m_SrcRect.x = 0;
				}
				m_LastSpriteUpdate = m_MaxSpriteUpdate;
			}
		}
		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(true);
		break;
	}
	case dae::AnimationState::Dead:
	{
		if (m_AnimStateDirty)
		{
			m_SrcRect.x = 0;
			m_SrcRect.y = spriteSizeY;
			m_SrcRect.w = spriteSizeX;
			m_SrcRect.h = spriteSizeY;
			m_AnimStateDirty = false;
		}
		else
		{
			m_DeadLastSpriteUpdate -= dT;
			if (m_DeadLastSpriteUpdate <= 0.f)
			{
				m_SrcRect.x += spriteSizeX;
				if (m_SrcRect.x > 3 * spriteSizeX)
				{
					m_SrcRect.x = 0;
				}
				m_DeadLastSpriteUpdate = m_DeadMaxSpriteUpdate;
			}
		}
		imgComp->SetSrcRect(m_SrcRect);
		imgComp->SetFlipped(false);
		break;
	}

	}



}

dae::EnemyComponent::EnemyComponent(dae::GameObject* pOwner, int score, GameObject* pPlayer)
	:BaseComponent(pOwner)
	, m_Score(score)
	,m_pPlayer(pPlayer)
{
	m_DeadLastSpriteUpdate = m_DeadMaxSpriteUpdate;
	m_LastSpriteUpdate = m_MaxSpriteUpdate;
}
