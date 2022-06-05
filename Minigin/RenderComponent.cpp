#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"

void dae::RenderComponent::Render()
{
	if (!m_Active)
		return;

	if (m_Texture != nullptr)
	{
		const auto& pos = GetTransform().GetPosition() + GetLocalTransform().GetPosition();
		if(m_SrcRect.w != 0.f)
		{
			dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect, SDL_Rect{ static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(m_Size.GetPosition().x), static_cast<int>(m_Size.GetPosition().y) }, m_Flipped);
		}
		else
		{
			if(m_Size.GetPosition().x != 0.f)
				dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Size.GetPosition().x, m_Size.GetPosition().y);
			else
				dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		}

	}
}