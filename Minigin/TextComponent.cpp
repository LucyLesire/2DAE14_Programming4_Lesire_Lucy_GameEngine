#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL_ttf.h>

void TextComponent::Update(float)
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
	}
}

TextComponent::TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font)
	:m_Text{text}
	,m_Font{font}
{
}

//void dae::TextObject::SetText(const std::string& text)
//{
//	m_Text = text;
//	m_NeedsUpdate = true;
//}
//
//void dae::TextObject::SetPosition(const float x, const float y)
//{
//	m_Transform.SetPosition(x, y, 0.0f);
//}
