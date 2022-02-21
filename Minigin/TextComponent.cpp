#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>

void dae::TextComponent::Update(float dT)
{
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { 255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(dae::Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<dae::Texture2D>(texture);
		m_NeedsUpdate = false;
		m_CanChange = false;
	}

	if (m_CanChange == false)
	{
		m_WaitBetweenUpdates += dT;
		if (m_WaitBetweenUpdates > m_MaxWait)
		{
			m_WaitBetweenUpdates = 0.f;
			m_CanChange = true;
		}
	}
}

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font)
	:m_Text{text}
	,m_Font{font}
{
}

void dae::TextComponent::SetText(const std::string& text)
{
	if (m_CanChange)
	{
		m_Text = text;
		m_NeedsUpdate = true;
	}
}
