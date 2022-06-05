#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include <SDL_rect.h>

namespace dae
{
	class Texture2D;
	class RenderComponent : public BaseComponent
	{
	public:

		virtual void Update(float deltaTime) = 0;
		virtual void LateUpdate(float) override = 0;
		void Render();

		RenderComponent(bool centered = false) : m_Centered(centered) {};
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		void SetSize(Transform2D size) { m_Size = size; }
		Transform2D GetSize() const { return m_Size; }

		void SetSrcRect(const SDL_Rect& srcRect) { m_SrcRect = srcRect; }

		void SetFlipped(bool enable) { m_Flipped = enable; }
		void SetActive(bool activate) { m_Active = activate; }
	protected:
		std::shared_ptr<dae::Texture2D> m_Texture;
		bool m_NeedsUpdate = false;

	private:
		bool m_Flipped{};
		Transform2D m_Size{};
		SDL_Rect m_SrcRect{};
		bool m_Active{ true };

		bool m_Centered{};
	};
}


