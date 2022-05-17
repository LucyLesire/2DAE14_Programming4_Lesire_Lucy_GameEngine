#include "MiniginPCH.h"
#include "RenderComponent.h"
#include "Renderer.h"
#include <SDL_ttf.h>

void dae::RenderComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto& pos = GetTransform().GetPosition();
		dae::Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}