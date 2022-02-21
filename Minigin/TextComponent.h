#pragma once
#include "RenderComponent.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Transform.h"
#include "Font.h"

namespace dae
{
	class TextComponent final : public RenderComponent
	{
	public:

		void Update(float deltaTime) override;
		void SetText(const std::string& text);

		explicit TextComponent(const std::string& text, const std::shared_ptr<dae::Font>& font);
		TextComponent() = default;
		virtual ~TextComponent() = default;
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

	private:
		std::string m_Text;
		std::shared_ptr<dae::Font> m_Font;
		bool m_NeedsUpdate = true;

		bool m_CanChange = true;
		float m_WaitBetweenUpdates = 0.f;
		const float m_MaxWait = 0.1f;
	};
}


